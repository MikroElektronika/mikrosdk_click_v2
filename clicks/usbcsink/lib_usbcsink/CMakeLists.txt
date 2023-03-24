cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbcsink LANGUAGES MikroC)
else()
    project(lib_usbcsink LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbcsink STATIC
        src/usbcsink.c
        include/usbcsink.h
)
add_library(Click.USBCSink  ALIAS lib_usbcsink)



target_include_directories(lib_usbcsink PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbcsink PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbcsink PUBLIC MikroSDK.Driver)
