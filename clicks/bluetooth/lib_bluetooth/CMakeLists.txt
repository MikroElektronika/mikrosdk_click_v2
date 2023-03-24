cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bluetooth LANGUAGES MikroC)
else()
    project(lib_bluetooth LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bluetooth STATIC
        src/bluetooth.c
        include/bluetooth.h
)
add_library(Click.Bluetooth  ALIAS lib_bluetooth)



target_include_directories(lib_bluetooth PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bluetooth PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bluetooth PUBLIC MikroSDK.Driver)
