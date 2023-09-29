cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digipot14 LANGUAGES MikroC)
else()
    project(lib_digipot14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digipot14 STATIC
        src/digipot14.c
        include/digipot14.h
)
add_library(Click.DIGIPOT14  ALIAS lib_digipot14)



target_include_directories(lib_digipot14 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digipot14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digipot14 PUBLIC MikroSDK.Driver)

