cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ble5 LANGUAGES MikroC)
else()
    project(lib_ble5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ble5 STATIC
        src/ble5.c
        include/ble5.h
)
add_library(Click.BLE5  ALIAS lib_ble5)



target_include_directories(lib_ble5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ble5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ble5 PUBLIC MikroSDK.Driver)

