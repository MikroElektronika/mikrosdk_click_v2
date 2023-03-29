cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rng LANGUAGES MikroC)
else()
    project(lib_rng LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rng STATIC
        src/rng.c
        include/rng.h
)
add_library(Click.Rng  ALIAS lib_rng)



target_include_directories(lib_rng PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rng PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rng PUBLIC MikroSDK.Driver)
