cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbcpower3 LANGUAGES MikroC)
else()
    project(lib_usbcpower3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbcpower3 STATIC
        src/usbcpower3.c
        include/usbcpower3.h
)
add_library(Click.USBCPower3  ALIAS lib_usbcpower3)



target_include_directories(lib_usbcpower3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbcpower3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbcpower3 PUBLIC MikroSDK.Driver)

