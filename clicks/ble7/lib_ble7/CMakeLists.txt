cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ble7 LANGUAGES MikroC)
else()
    project(lib_ble7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ble7 STATIC
        src/ble7.c
        include/ble7.h
)
add_library(Click.Ble7  ALIAS lib_ble7)



target_include_directories(lib_ble7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ble7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ble7 PUBLIC MikroSDK.Driver)
