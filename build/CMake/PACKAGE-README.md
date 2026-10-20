# FreeStick binary release package

Each ZIP contains a Release library in `lib/`, public headers in `inc/`, EELog
headers in `src/3rdParty/EELog/src/`, and build/version information in
`build-info.json`. Keep that directory structure: public headers reference EELog
by relative path. Add `inc/` to your compiler's include paths and include
`freestick.h`. Copyright and license notices are retained in the headers.

These are native libraries; Qt is not required. Link the matching library and
the dependencies below. These packages do not provide a CMake `find_package`
configuration. Use a compatible C++ toolchain and runtime for your application.

| Package | Library and requirements |
| --- | --- |
| macos-universal | Static, arm64 + x86_64, deployment target macOS 12. Link Foundation, GameController, CoreHaptics, CoreFoundation, IOKit and ForceFeedback frameworks. |
| windows-x64 | Static, MSVC 2022 x64, Release `/MD` runtime. Link xinput, dinput8, dxguid, user32, ole32, oleaut32 and comctl32. Use a compatible Visual C++ redistributable. |
| linux-x64 | Static, Ubuntu 22.04 GCC/libstdc++. **NULL backend only: no Linux hardware controller input yet.** |
| android-* | Shared, NDK 27.2.12479018, API 28+, named ABI, shared libc++. Package both `.so` files in that ABI's `jniLibs` directory; avoid conflicting copies of libc++ from other dependencies. Include/adapt `android/java` in the Android host app and initialize its existing Activity bridge. This is not an AAR or APK. |
| ios-arm64 | Static, physical iOS devices, deployment target iOS 15. Link Foundation, GameController and CoreHaptics. |
| ios-simulator-universal | Static, arm64 + x86_64 simulator, deployment target iOS 15. Same frameworks as iOS device. Existing FreeStick headers select the NULL backend in the simulator. |

iOS device and simulator libraries are separate, not interchangeable. These ZIPs
are not XCFrameworks. Libraries are unsigned; the consuming app handles signing.
Android packages include the NDK notice for the bundled C++ runtime.

The workflow compiles all platforms and runs a desktop initialization smoke test.
That does not validate controller hardware, older OS runtime compatibility, or
mobile app integration. The macOS deployment target permits Monterey, but the
hosted runner uses a newer Xcode SDK; this is not an Xcode 14.2 validation job.
