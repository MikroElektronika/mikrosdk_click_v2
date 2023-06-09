cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digipot12 LANGUAGES MikroC)
else()
    project(lib_digipot12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digipot12 STATIC
        src/digipot12.c
        include/digipot12.h
)
add_library(Click.DIGIPOT12  ALIAS lib_digipot12)



target_include_directories(lib_digipot12 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digipot12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digipot12 PUBLIC MikroSDK.Driver)

