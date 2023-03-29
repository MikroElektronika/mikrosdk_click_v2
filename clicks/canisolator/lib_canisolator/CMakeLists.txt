cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_canisolator LANGUAGES MikroC)
else()
    project(lib_canisolator LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_canisolator STATIC
        src/canisolator.c
        include/canisolator.h
)
add_library(Click.CanIsolator  ALIAS lib_canisolator)



target_include_directories(lib_canisolator PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_canisolator PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_canisolator PUBLIC MikroSDK.Driver)
