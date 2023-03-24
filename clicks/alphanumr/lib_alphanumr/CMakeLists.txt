cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_alphanumr LANGUAGES MikroC)
else()
    project(lib_alphanumr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_alphanumr STATIC
        src/alphanumr.c
        include/alphanumr.h
)
add_library(Click.AlphaNumR  ALIAS lib_alphanumr)



target_include_directories(lib_alphanumr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_alphanumr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_alphanumr PUBLIC MikroSDK.Driver)
