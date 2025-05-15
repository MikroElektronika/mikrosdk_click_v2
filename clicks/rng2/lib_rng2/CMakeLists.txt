cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rng2 LANGUAGES MikroC)
else()
    project(lib_rng2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rng2 STATIC
        src/rng2.c
        include/rng2.h
)
add_library(Click.RNG2  ALIAS lib_rng2)



target_include_directories(lib_rng2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rng2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rng2 PUBLIC MikroSDK.Driver)

