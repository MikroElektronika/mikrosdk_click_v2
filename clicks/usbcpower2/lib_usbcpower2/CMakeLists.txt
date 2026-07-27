cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbcpower2 LANGUAGES MikroC)
else()
    project(lib_usbcpower2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbcpower2 STATIC
        src/usbcpower2.c
        include/usbcpower2.h
)
add_library(Click.USBCPower2  ALIAS lib_usbcpower2)



target_include_directories(lib_usbcpower2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbcpower2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbcpower2 PUBLIC MikroSDK.Driver)

