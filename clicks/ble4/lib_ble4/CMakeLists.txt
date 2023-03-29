cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ble4 LANGUAGES MikroC)
else()
    project(lib_ble4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ble4 STATIC
        src/ble4.c
        include/ble4.h
)
add_library(Click.BLE4  ALIAS lib_ble4)



target_include_directories(lib_ble4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ble4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ble4 PUBLIC MikroSDK.Driver)
