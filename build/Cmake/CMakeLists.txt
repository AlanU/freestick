cmake_minimum_required(VERSION 3.20.2)
project(FreeStick)

set(CMAKE_CXX_STANDARD 11)

# Set the default library type to STATIC
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Define the source and header directories
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../inc")

# Debug print the directories
message(STATUS "Source directory: ${SOURCE_DIR}")
message(STATUS "Include directory: ${INCLUDE_DIR}")

# Collect base sources and headers with explicit paths
set(BASE_SOURCES
        ${SOURCE_DIR}/baseClasses/FSBaseManager.cpp
        ${SOURCE_DIR}/baseClasses/FSBaseDevice.cpp
        ${SOURCE_DIR}/USB/common/FSUSBDevice.cpp
        ${SOURCE_DIR}/USB/common/FSUSBDeviceManager.cpp
        ${SOURCE_DIR}/USB/platform/NULL/FSNULLJoystickDeviceManager.cpp
        ${SOURCE_DIR}/3rdParty/EELog/src/EELog.cpp
        ${SOURCE_DIR}/FSDeviceInputEvent.cpp
)

# Platform-specific configurations
if(ANDROID)
    set(PLATFORM_SOURCES
            ${SOURCE_DIR}/USB/platform/Android/jni/src/FSAndroidJoystick.cpp
            ${SOURCE_DIR}/USB/platform/Android/jni/src/FSAndroidJoystickManager.cpp
    )

    set(NDK_ROOT $ENV{ANDROID_NDK_ROOT})
    if(NOT EXISTS ${NDK_ROOT})
        set(NDK_ROOT $ENV{DEFAULT_ANDROID_NDK_ROOT})
    endif()

    include_directories(
            ${JAVA_HOME}/include
            ${JAVA_HOME}/include/darwin
            ${JAVA_HOME}/include/win32
            ${JAVA_HOME}/include/linux
            ${NDK_ROOT}/sources/android
    )

elseif(WIN32)
    set(PLATFORM_SOURCES
            ${SOURCE_DIR}/USB/platform/Windows/FSWindowsJoystick.cpp
            ${SOURCE_DIR}/USB/platform/Windows/FSWindowsJoystickDeviceManager.cpp
    )

elseif(APPLE)
    set(PLATFORM_SOURCES
            ${SOURCE_DIR}/3rdParty/Mac/IOHID/IOHIDDevice_.c
            ${SOURCE_DIR}/3rdParty/Mac/IOHID/IOHIDElement_.c
            ${SOURCE_DIR}/USB/platform/MacOSX/FSUSBMacOSXJoystick.cpp
            ${SOURCE_DIR}/USB/platform/MacOSX/FSMacOSXJoystickDeviceManager.cpp
            ${SOURCE_DIR}/USB/platform/iOS/FSMFIJoystickManager.mm
            ${SOURCE_DIR}/USB/platform/iOS/FSMFIJoystick.mm
            ${SOURCE_DIR}/USB/platform/MacOSX/FSUSBMacOSXJoystickDeviceManager.mm
            ${SOURCE_DIR}/USB/platform/MacOSX/FSMacUtil.mm
    )

elseif(UNIX)
    include_directories(/usr/include/libevdev-1.0)
    link_directories(/usr/lib/x86_64-linux-gnu/)

    set(PLATFORM_SOURCES
            ${SOURCE_DIR}/USB/platform/Linux/FSLinuxJoystickDeviceManager.cpp
            ${SOURCE_DIR}/USB/platform/Linux/FSLinuxJoystick.cpp
    )
endif()

# Set the include directories globally
include_directories(
        ${INCLUDE_DIR}
        ${INCLUDE_DIR}/common
        ${INCLUDE_DIR}/baseClasses
        ${INCLUDE_DIR}/Interfaces
        ${INCLUDE_DIR}/USB/common
        ${INCLUDE_DIR}/USB
        ${INCLUDE_DIR}/USB/platform/NULL
        ${INCLUDE_DIR}/3rdParty/EELog/src
)

# Combine all sources
set(ALL_SOURCES ${BASE_SOURCES} ${PLATFORM_SOURCES})

# Debug print the sources
message(STATUS "Base sources: ${BASE_SOURCES}")
message(STATUS "Platform sources: ${PLATFORM_SOURCES}")
message(STATUS "All sources: ${ALL_SOURCES}")

# Verify that we have sources before creating the target
list(LENGTH ALL_SOURCES SOURCE_COUNT)
if(SOURCE_COUNT EQUAL 0)
    message(FATAL_ERROR "No source files found! Please check the paths.")
endif()

# Create the FreeStick static library target
add_library(FreeStick STATIC ${ALL_SOURCES})

# Platform-specific linking
if(UNIX AND NOT APPLE)
    target_link_libraries(FreeStick PRIVATE evdev)
elseif(WIN32)
    target_link_libraries(FreeStick PRIVATE Xinput User32)
elseif(APPLE)
    target_link_libraries(FreeStick PRIVATE
            IOKit
            ForceFeedback
            CoreFoundation
            GameController
            Foundation
            CoreHaptics
    )
endif()

# Output directories based on build type
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# Set the target install location
if(ANDROID)
    set(TARGET_PATH "/libs/armeabi-v7a")
    install(TARGETS FreeStick DESTINATION ${TARGET_PATH})
elseif(UNIX AND NOT APPLE)
    if(EXISTS "/opt/usr/lib")
        install(TARGETS FreeStick DESTINATION /opt/usr/lib)
    else()
        install(TARGETS FreeStick DESTINATION /usr/lib)
    endif()
endif()

# Handle Debug/Release configurations
set_target_properties(FreeStick PROPERTIES DEBUG_POSTFIX "d")

# Custom clean rule
add_custom_target(clean-all
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/debug
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/release
)

# Debug and Release build directories
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(FreeStick PROPERTIES OUTPUT_NAME "FreeStick")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
else()
    set_target_properties(FreeStick PROPERTIES OUTPUT_NAME "FreeStickDebug")
endif()