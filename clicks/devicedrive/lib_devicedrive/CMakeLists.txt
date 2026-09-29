cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_devicedrive LANGUAGES MikroC)
else()
    project(lib_devicedrive LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_devicedrive STATIC
        src/devicedrive.c
        include/devicedrive.h
)
add_library(Click.DeviceDrive  ALIAS lib_devicedrive)



target_include_directories(lib_devicedrive PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_devicedrive PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_devicedrive PUBLIC MikroSDK.Driver)

