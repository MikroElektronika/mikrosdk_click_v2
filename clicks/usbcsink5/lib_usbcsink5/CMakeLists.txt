cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbcsink5 LANGUAGES MikroC)
else()
    project(lib_usbcsink5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbcsink5 STATIC
        src/usbcsink5.c
        include/usbcsink5.h
)
add_library(Click.USBCSink5  ALIAS lib_usbcsink5)



target_include_directories(lib_usbcsink5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbcsink5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbcsink5 PUBLIC MikroSDK.Driver)

