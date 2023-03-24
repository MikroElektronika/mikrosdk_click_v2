cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digipot8 LANGUAGES MikroC)
else()
    project(lib_digipot8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digipot8 STATIC
        src/digipot8.c
        include/digipot8.h
)
add_library(Click.DIGIPOT8  ALIAS lib_digipot8)



target_include_directories(lib_digipot8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digipot8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digipot8 PUBLIC MikroSDK.Driver)
