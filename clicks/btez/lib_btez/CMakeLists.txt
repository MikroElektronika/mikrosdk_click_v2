cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_btez LANGUAGES MikroC)
else()
    project(lib_btez LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_btez STATIC
        src/btez.c
        include/btez.h
)
add_library(Click.BtEz  ALIAS lib_btez)



target_include_directories(lib_btez PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_btez PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_btez PUBLIC MikroSDK.Driver)
