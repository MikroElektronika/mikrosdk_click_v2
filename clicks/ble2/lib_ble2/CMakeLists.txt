cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ble2 LANGUAGES MikroC)
else()
    project(lib_ble2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ble2 STATIC
        src/ble2.c
        include/ble2.h
)
add_library(Click.BLE2  ALIAS lib_ble2)



target_include_directories(lib_ble2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ble2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ble2 PUBLIC MikroSDK.Driver)

