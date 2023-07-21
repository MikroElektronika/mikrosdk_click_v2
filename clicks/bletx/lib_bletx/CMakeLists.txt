cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bletx LANGUAGES MikroC)
else()
    project(lib_bletx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bletx STATIC
        src/bletx.c
        include/bletx.h
)
add_library(Click.BleTx  ALIAS lib_bletx)



target_include_directories(lib_bletx PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bletx PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bletx PUBLIC MikroSDK.Driver)
