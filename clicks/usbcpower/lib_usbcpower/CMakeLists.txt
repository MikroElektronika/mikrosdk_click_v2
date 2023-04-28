cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbcpower LANGUAGES MikroC)
else()
    project(lib_usbcpower LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbcpower
STATIC
src/usbcpower.c
include/usbcpower.h
include/usbcpower_config.h
)
add_library(Click.USBCPower  ALIAS lib_usbcpower)



target_include_directories(lib_usbcpower PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbcpower PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbcpower PUBLIC MikroSDK.Driver)

