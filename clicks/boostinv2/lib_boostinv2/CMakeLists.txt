cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_boostinv2 LANGUAGES MikroC)
else()
    project(lib_boostinv2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_boostinv2 STATIC
        src/boostinv2.c
        include/boostinv2.h
)
add_library(Click.BoostInv2  ALIAS lib_boostinv2)



target_include_directories(lib_boostinv2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_boostinv2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_boostinv2 PUBLIC MikroSDK.Driver)
