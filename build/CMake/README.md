# FreeStick CMake build

## GitHub Actions release packages

The FreeStick repository's `.github/workflows/cmake-packages.yml` builds Release
ZIPs on pull requests, pushes to `master`, `v*` tags, and manual **Run workflow**
requests. Commit the workflow and CMake files to the **FreeStick repository**;
GitHub does not execute workflows inside a submodule of Gamepad Inspector.

The matrix produces universal macOS, Windows x64, Linux x64, four Android ABIs,
iOS arm64 device, and universal iOS simulator packages. Each job uploads an
artifact containing a versioned ZIP and SHA-256 checksum. Download it from the
workflow run's **Artifacts** section; the inner ZIP is the release package.
Artifacts expire after 30 days. Attach the ZIPs to a GitHub Release for permanent
distribution; this workflow does not create or publish a release automatically.

Package contents and link requirements are described in [PACKAGE-README.md](PACKAGE-README.md).
The helper can also be run from any directory on the matching platform:

```sh
python3 build/CMake/package.py --package macos-universal
```

The example above assumes your working directory is the FreeStick root. Use
`--cmake /path/to/cmake` if needed. Android builds require `ANDROID_NDK_ROOT` to
point to NDK 27.2.12479018; Actions installs it automatically. Generated builds
and packages stay inside the already-ignored `build/CMake/out/` directory.

Hosted runner images follow [GitHub's runner image list](https://github.com/actions/runner-images).
Apple jobs use the runner's default Xcode; they do not test the older Xcode 14.2
toolchain. Their deployment targets are macOS 12 and iOS 15.

This entry point lives beside `build/QT`; sources stay in their original locations.
FreeStick and CommandLineHarness do not depend on Qt. Requires CMake 3.21+ and a
C++11 compiler, plus the platform SDK. Existing qmake projects remain available.

Run these commands from the FreeStick repository root. Keep generated files in
`build/CMake/out/<platform>-<configuration>` (ignored by Git), or another separate
binary directory. Never use the same binary directory for different toolchains.

## Desktop (macOS, Windows, Linux)

```sh
cmake -S build/CMake -B build/CMake/out/desktop-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build/CMake/out/desktop-debug --config Debug --parallel
```

On macOS/Linux with Makefiles or Ninja, run:

```sh
build/CMake/out/desktop-debug/CommandLineHarness --smoke-test
build/CMake/out/desktop-debug/CommandLineHarness
```

With Visual Studio, the executable is normally
`build/CMake/out/desktop-debug/Debug/CommandLineHarness.exe`.
Use a Visual Studio developer shell on Windows. For Release, use a separate
binary directory and `-DCMAKE_BUILD_TYPE=Release`; for Visual Studio or Xcode,
select `--config Release` instead.

The harness writes startup and controller event messages directly to `std::cout`,
independently of FreeStick's logging. The library keeps its default disabled
EELog configuration; the harness does not enable library diagnostics. This also
applies to Release builds and the existing qmake harness project.

The smoke test initializes the platform manager, updates once, and exits without
opening the Mac HUD. It checks startup/linkage, not physical controller behavior.
The normal Mac harness runs an AppKit event loop; use its Quit menu to exit.
On Windows/Linux, enter `q` then Return to exit (EOF also exits).
**Linux currently uses FreeStick's existing NULL backend; it has no hardware
controller support.** Adding a Linux backend is separate from this build migration.

For a universal macOS library/executable, add
`-DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"` when configuring a fresh binary directory.
Set `CMAKE_OSX_DEPLOYMENT_TARGET` explicitly if you require an older Apple OS.

If CMake is not on PATH, Qt's installation may provide it; on this development
Mac it is `/Users/alan/Qt/Tools/CMake/CMake.app/Contents/bin/cmake`.
Qt Creator can open this directory's `CMakeLists.txt` with a desktop kit.

## Android native library

```sh
cmake -S build/CMake -B build/CMake/out/android-arm64 \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake" \
  -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-28 \
  -DCMAKE_BUILD_TYPE=Debug
cmake --build build/CMake/out/android-arm64 --parallel
```

This produces `libFreeStick.so`. The NDK supplies JNI headers; a host JDK include
path is not needed to compile the native library. The consuming Android app must
still package the existing Java bridge in `src/USB/platform/Android/java` and
initialize it through its Activity. This build does not create an APK or validate
Java integration. Choose API level and ABI to match the consuming application.

## iOS library

```sh
cmake -S build/CMake -B build/CMake/out/ios -G Xcode \
  -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphoneos \
  -DCMAKE_OSX_ARCHITECTURES=arm64
cmake --build build/CMake/out/ios --config Debug --target FreeStick -- \
  CODE_SIGNING_ALLOWED=NO
```

For a simulator library, configure a separate directory with
`-DCMAKE_OSX_SYSROOT=iphonesimulator` and the desired simulator architecture.
FreeStick's public header currently selects the NULL backend for iOS simulators.
The desktop command-line harness is disabled for iOS and Android; physical input
on those platforms requires a host app and device testing.

Toolchain configuration follows the [CMake toolchains documentation](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html).

## Integration with the future application CMake build

```cmake
add_subdirectory("${PROJECT_SOURCE_DIR}/3rdParty/freestick/build/CMake"
                 "${CMAKE_CURRENT_BINARY_DIR}/freestick")
target_link_libraries(MyApplication PRIVATE FreeStick::FreeStick)
```

The target carries its public include directory, C++ requirement and platform
link dependencies. The harness defaults to ON for standalone desktop builds and
OFF when included by another project; override with `FREESTICK_BUILD_HARNESS`.
FreeStick remains static on desktop/iOS and shared on Android, matching qmake.
Apple library Objective-C++ sources use ARC; the existing Mac harness retains its
manual memory management. No application migration or installation/export package
is included in this first phase.

## Migration validation

Verified on the development Mac:

- macOS Debug: library and harness build; `--smoke-test` exits successfully.
- macOS Release: universal arm64/x86_64 library and harness build; smoke test exits
  successfully on the host architecture.
- Android: ARM64 shared library builds with NDK 27.2.12479018, API 28.
- iOS: ARM64 Debug static library builds with Xcode and the iOS 26.5 SDK,
  with signing disabled.

Windows and Linux builds still need native validation. Mobile device runtime,
iOS simulator, older OS deployment targets, and actual controller events have
not been validated. Existing compiler warnings remain.
