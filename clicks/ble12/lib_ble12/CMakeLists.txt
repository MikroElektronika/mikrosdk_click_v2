cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ble12 LANGUAGES MikroC)
else()
    project(lib_ble12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ble12 STATIC
        src/ble12.c
        include/ble12.h
)
add_library(Click.BLE12  ALIAS lib_ble12)



target_include_directories(lib_ble12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ble12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ble12 PUBLIC MikroSDK.Driver)
