cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digipot LANGUAGES MikroC)
else()
    project(lib_digipot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digipot STATIC
        src/digipot.c
        include/digipot.h
)
add_library(Click.DigiPot  ALIAS lib_digipot)



target_include_directories(lib_digipot PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digipot PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digipot PUBLIC MikroSDK.Driver)
