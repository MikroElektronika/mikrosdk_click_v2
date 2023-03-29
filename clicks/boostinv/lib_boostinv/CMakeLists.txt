cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_boostinv LANGUAGES MikroC)
else()
    project(lib_boostinv LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_boostinv STATIC
        src/boostinv.c
        include/boostinv.h
)
add_library(Click.BoostInv  ALIAS lib_boostinv)



target_include_directories(lib_boostinv PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_boostinv PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_boostinv PUBLIC MikroSDK.Driver)
