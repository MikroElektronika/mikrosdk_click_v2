cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbcsink4 LANGUAGES MikroC)
else()
    project(lib_usbcsink4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbcsink4 STATIC
        src/usbcsink4.c
        include/usbcsink4.h
)
add_library(Click.USBCSink4  ALIAS lib_usbcsink4)



target_include_directories(lib_usbcsink4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbcsink4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbcsink4 PUBLIC MikroSDK.Driver)

