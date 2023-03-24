cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digipot3 LANGUAGES MikroC)
else()
    project(lib_digipot3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digipot3 STATIC
        src/digipot3.c
        include/digipot3.h
)
add_library(Click.DigiPot3  ALIAS lib_digipot3)



target_include_directories(lib_digipot3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digipot3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digipot3 PUBLIC MikroSDK.Driver)
