cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbcsource LANGUAGES MikroC)
else()
    project(lib_usbcsource LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbcsource STATIC
        src/usbcsource.c
        include/usbcsource.h
)
add_library(Click.USBCSource  ALIAS lib_usbcsource)



target_include_directories(lib_usbcsource PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbcsource PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbcsource PUBLIC MikroSDK.Driver)
