cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbmux LANGUAGES MikroC)
else()
    project(lib_usbmux LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbmux STATIC
        src/usbmux.c
        include/usbmux.h
)
add_library(Click.USBMUX  ALIAS lib_usbmux)



target_include_directories(lib_usbmux PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbmux PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbmux PUBLIC MikroSDK.Driver)

