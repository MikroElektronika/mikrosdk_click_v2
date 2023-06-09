cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ble8 LANGUAGES MikroC)
else()
    project(lib_ble8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ble8 STATIC
        src/ble8.c
        include/ble8.h
)
add_library(Click.Ble8  ALIAS lib_ble8)



target_include_directories(lib_ble8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ble8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ble8 PUBLIC MikroSDK.Driver)
