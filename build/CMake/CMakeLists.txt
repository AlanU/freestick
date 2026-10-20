cmake_minimum_required(VERSION 3.21)
project(FreeStick VERSION 0.0.5 LANGUAGES C CXX)

get_filename_component(FREESTICK_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Use a separate build directory: cmake -S . -B out/debug")
endif()

set(_harness_default OFF)
if(PROJECT_IS_TOP_LEVEL AND NOT ANDROID AND NOT CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(_harness_default ON)
endif()
option(FREESTICK_BUILD_HARNESS "Build the desktop command-line harness" ${_harness_default})

# Preserve qmake's shared Android library and static desktop/iOS libraries.
if(ANDROID)
    add_library(FreeStick SHARED)
else()
    add_library(FreeStick STATIC)
endif()
add_library(FreeStick::FreeStick ALIAS FreeStick)
target_compile_features(FreeStick PUBLIC cxx_std_11)
set_target_properties(FreeStick PROPERTIES CXX_EXTENSIONS OFF POSITION_INDEPENDENT_CODE ON)
target_include_directories(FreeStick PUBLIC "${FREESTICK_ROOT}/inc")
target_sources(FreeStick PRIVATE
    "${FREESTICK_ROOT}/src/FSDeviceInputEvent.cpp"
    "${FREESTICK_ROOT}/src/baseClasses/FSBaseDevice.cpp"
    "${FREESTICK_ROOT}/src/baseClasses/FSBaseEvent.cpp"
    "${FREESTICK_ROOT}/src/baseClasses/FSBaseJoystickInfo.cpp"
    "${FREESTICK_ROOT}/src/baseClasses/FSBaseManager.cpp"
    "${FREESTICK_ROOT}/src/USB/common/FSMultJoystickDeviceManger.cpp"
    "${FREESTICK_ROOT}/src/USB/common/FSSpinlock.cpp"
    "${FREESTICK_ROOT}/src/USB/common/FSUSBDevice.cpp"
    "${FREESTICK_ROOT}/src/USB/common/FSUSBDeviceManager.cpp"
    "${FREESTICK_ROOT}/src/USB/common/FSUSBJoyStickInputElement.cpp"
    "${FREESTICK_ROOT}/src/USB/common/FSUSBJoystick.cpp"
    "${FREESTICK_ROOT}/src/USB/common/FSUSBJoystickButton.cpp"
    "${FREESTICK_ROOT}/src/USB/common/FSUSBJoystickDeviceManager.cpp"
    "${FREESTICK_ROOT}/src/USB/common/FSUpdatableJoystickDeviceManager.cpp"
    "${FREESTICK_ROOT}/src/USB/platform/NULL/FSUSBNullDevice.cpp"
    "${FREESTICK_ROOT}/src/USB/platform/NULL/FSUSBNullJoystickDeviceManager.cpp"
    "${FREESTICK_ROOT}/src/3rdParty/EELog/src/EELog.cpp"
    "${FREESTICK_ROOT}/src/3rdParty/EELog/src/EENullStream.cpp"
    "${FREESTICK_ROOT}/src/3rdParty/EELog/src/EEStream.cpp"
)

if(APPLE)
    enable_language(OBJCXX)
    set_target_properties(FreeStick PROPERTIES OBJCXX_STANDARD 11 OBJCXX_STANDARD_REQUIRED YES
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES)
    target_compile_options(FreeStick PRIVATE "$<$<COMPILE_LANGUAGE:OBJCXX>:-fobjc-arc>")
    target_sources(FreeStick PRIVATE
        "${FREESTICK_ROOT}/src/USB/platform/iOS/FSMFIJoystick.mm"
        "${FREESTICK_ROOT}/src/USB/platform/iOS/FSMFIJoystickManager.mm"
    )
    set(_frameworks Foundation GameController CoreHaptics)
    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        target_sources(FreeStick PRIVATE
            "${FREESTICK_ROOT}/src/3rdParty/Mac/IOHID/IOHIDDevice_.c"
            "${FREESTICK_ROOT}/src/3rdParty/Mac/IOHID/IOHIDElement_.c"
            "${FREESTICK_ROOT}/src/3rdParty/Mac/IOHID/ImmrHIDUtilAddOn.c"
            "${FREESTICK_ROOT}/src/USB/platform/MacOSX/FSMacOSXJoystickDeviceManager.cpp"
            "${FREESTICK_ROOT}/src/USB/platform/MacOSX/FSUSBMacOSXJoystick.cpp"
            "${FREESTICK_ROOT}/src/USB/platform/MacOSX/FSMacUtil.mm"
            "${FREESTICK_ROOT}/src/USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.mm"
        )
        list(APPEND _frameworks IOKit ForceFeedback CoreFoundation)
    elseif(NOT CMAKE_SYSTEM_NAME STREQUAL "iOS")
        message(FATAL_ERROR "Unsupported Apple platform: ${CMAKE_SYSTEM_NAME}")
    endif()
    foreach(_framework IN LISTS _frameworks)
        find_library(FREESTICK_${_framework}_LIBRARY NAMES ${_framework} REQUIRED)
        target_link_libraries(FreeStick PUBLIC "${FREESTICK_${_framework}_LIBRARY}")
    endforeach()
elseif(WIN32)
    target_sources(FreeStick PRIVATE
        "${FREESTICK_ROOT}/src/USB/platform/Windows/FSDirectInputJoystick.cpp"
        "${FREESTICK_ROOT}/src/USB/platform/Windows/FSDirectInputJoystickManager.cpp"
        "${FREESTICK_ROOT}/src/USB/platform/Windows/FSWindowsJoystickDeviceManager.cpp"
        "${FREESTICK_ROOT}/src/USB/platform/Windows/FSXInputJoystick.cpp"
        "${FREESTICK_ROOT}/src/USB/platform/Windows/FSXInputJoystickDeviceManager.cpp"
    )
    target_link_libraries(FreeStick PUBLIC xinput dinput8 dxguid user32 ole32 oleaut32 comctl32)
elseif(ANDROID)
    target_sources(FreeStick PRIVATE
        "${FREESTICK_ROOT}/src/USB/platform/Android/jni/src/FSAndroidJoystick.cpp"
        "${FREESTICK_ROOT}/src/USB/platform/Android/jni/src/FSHIDAndroidJoysickDeviceManager.cpp"
        "${FREESTICK_ROOT}/src/USB/platform/Android/jni/src/FSJNI_Wrapper.cpp"
    )
    target_link_libraries(FreeStick PRIVATE android log)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "FreeStick: Linux uses the existing NULL backend (no hardware input)")
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

if(FREESTICK_BUILD_HARNESS)
    if(ANDROID OR CMAKE_SYSTEM_NAME STREQUAL "iOS")
        message(FATAL_ERROR "CommandLineHarness is a desktop executable; use FREESTICK_BUILD_HARNESS=OFF for mobile")
    endif()
    set(_harness_dir "${FREESTICK_ROOT}/build/QT/CommandLineHarness")
    add_executable(CommandLineHarness "${_harness_dir}/main.cpp")
    target_include_directories(CommandLineHarness PRIVATE "${FREESTICK_ROOT}/src")
    find_package(Threads REQUIRED)
    target_link_libraries(CommandLineHarness PRIVATE FreeStick::FreeStick Threads::Threads)
    if(APPLE)
        target_sources(CommandLineHarness PRIVATE "${_harness_dir}/MacOSHUD.mm")
        find_library(FREESTICK_AppKit_LIBRARY NAMES AppKit REQUIRED)
        target_link_libraries(CommandLineHarness PRIVATE "${FREESTICK_AppKit_LIBRARY}")
    endif()
endif()
