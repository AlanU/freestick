"""Build one release package, locally or in the FreeStick repository's Actions job."""

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import zipfile


PACKAGES = (
    "macos-universal", "windows-x64", "linux-x64", "ios-arm64",
    "ios-simulator-universal", "android-arm64-v8a", "android-armeabi-v7a",
    "android-x86", "android-x86_64",
)


def run(*args, **kwargs):
    subprocess.run([str(arg) for arg in args], check=True, **kwargs)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--package", choices=PACKAGES,
                        default=os.environ.get("FREESTICK_PACKAGE"))
    parser.add_argument("--cmake", default="cmake")
    args = parser.parse_args()
    if args.package is None:
        parser.error("provide --package or FREESTICK_PACKAGE")

    source = Path(__file__).resolve().parent
    root = source.parent.parent
    build = source / "out" / ("package-" + args.package)
    output = source / "out" / "packages"
    libdir = build / "lib"
    desktop = args.package.startswith(("macos-", "windows-", "linux-"))
    android = args.package.startswith("android-")
    options = [
        "-DCMAKE_BUILD_TYPE=Release",
        "-DFREESTICK_BUILD_HARNESS=" + ("ON" if desktop else "OFF"),
        "-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE=" + str(libdir),
        "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE=" + str(libdir),
        "-DCMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE=" + str(build / "bin"),
    ]
    runtime = None
    if args.package == "windows-x64":
        options += ["-G", "Visual Studio 17 2022", "-A", "x64",
                    "-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDLL"]
    elif args.package == "macos-universal":
        options += ["-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64",
                    "-DCMAKE_OSX_DEPLOYMENT_TARGET=12.0"]
    elif args.package.startswith("ios-"):
        simulator = args.package == "ios-simulator-universal"
        options += ["-G", "Xcode", "-DCMAKE_SYSTEM_NAME=iOS",
                    "-DCMAKE_OSX_SYSROOT=" + ("iphonesimulator" if simulator else "iphoneos"),
                    "-DCMAKE_OSX_ARCHITECTURES=" + ("arm64;x86_64" if simulator else "arm64"),
                    "-DCMAKE_OSX_DEPLOYMENT_TARGET=15.0"]
    elif android:
        ndk = Path(os.environ["ANDROID_NDK_ROOT"]).resolve()
        abi = args.package.removeprefix("android-")
        options += ["-DCMAKE_TOOLCHAIN_FILE=" + str(ndk / "build/cmake/android.toolchain.cmake"),
                    "-DANDROID_ABI=" + abi, "-DANDROID_PLATFORM=android-28",
                    "-DANDROID_STL=c++_shared", "-DANDROID_SUPPORT_FLEXIBLE_PAGE_SIZES=ON"]
        triple = {"arm64-v8a": "aarch64-linux-android", "armeabi-v7a": "arm-linux-androideabi",
                  "x86": "i686-linux-android", "x86_64": "x86_64-linux-android"}[abi]
        runtimes = list((ndk / "toolchains/llvm/prebuilt").glob(
            "*/sysroot/usr/lib/" + triple + "/libc++_shared.so"))
        if len(runtimes) != 1:
            raise RuntimeError("Could not uniquely locate Android libc++_shared.so")
        runtime = runtimes[0]

    run(args.cmake, "-S", source, "-B", build, *options)
    build_args = [args.cmake, "--build", build, "--config", "Release", "--parallel", "4"]
    if args.package.startswith("ios-"):
        build_args += ["--", "CODE_SIGNING_ALLOWED=NO"]
    run(*build_args)
    if desktop:
        exe = "CommandLineHarness.exe" if args.package == "windows-x64" else "CommandLineHarness"
        run(build / "bin" / exe, "--smoke-test", timeout=30)

    library = libdir / ("FreeStick.lib" if args.package == "windows-x64" else
                        "libFreeStick.so" if android else "libFreeStick.a")
    if not library.is_file():
        raise RuntimeError("Expected library missing: " + str(library))
    header = (root / "inc/freestick.h").read_text()
    version = ".".join(re.search(r"#define FREESTICK_VERSION_" + part + r"\s+(\d+)", header)[1]
                       for part in ("MAJOR", "MINOR", "PATCH"))
    revision = subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=root, text=True).strip()
    name = f"FreeStick-{version}-{args.package}-Release-{revision[:12]}"
    output.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="freestick-package-") as temporary:
        stage = Path(temporary) / name
        (stage / "lib").mkdir(parents=True)
        shutil.copy2(library, stage / "lib" / library.name)
        for headers in (root / "inc", root / "src/3rdParty/EELog/src"):
            for path in sorted(headers.rglob("*.h")):
                destination = stage / path.relative_to(root)
                destination.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(path, destination)
        if android:
            shutil.copy2(runtime, stage / "lib/libc++_shared.so")
            shutil.copytree(root / "src/USB/platform/Android/java", stage / "android/java")
            shutil.copy2(ndk / "NOTICE", stage / "ANDROID-NDK-NOTICE.txt")
        shutil.copy2(root / "README.md", stage / "FREESTICK-README.md")
        shutil.copy2(source / "PACKAGE-README.md", stage / "README.md")
        metadata = {
            "version": version, "commit": revision, "package": args.package,
            "configuration": "Release", "cmake_options": options,
            "cmake_version": subprocess.check_output([args.cmake, "--version"], text=True),
            "github_run_id": os.environ.get("GITHUB_RUN_ID"),
        }
        (stage / "build-info.json").write_text(json.dumps(metadata, indent=2) + "\n")
        archive = output / (name + ".zip")
        with zipfile.ZipFile(archive, "w", zipfile.ZIP_DEFLATED) as bundle:
            for path in sorted(stage.rglob("*")):
                if path.is_file():
                    bundle.write(path, path.relative_to(stage.parent))
        # Verify the ZIP can be read before advertising it as a release artifact.
        with zipfile.ZipFile(archive) as bundle:
            if bundle.testzip() is not None:
                raise RuntimeError("ZIP integrity check failed")
        digest = hashlib.sha256(archive.read_bytes()).hexdigest()
        archive.with_suffix(".zip.sha256").write_text(f"{digest}  {archive.name}\n")
        print("Created", archive)


if __name__ == "__main__":
    main()
