cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digipot7 LANGUAGES MikroC)
else()
    project(lib_digipot7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digipot7 STATIC
        src/digipot7.c
        include/digipot7.h
)
add_library(Click.DIGIPOT7  ALIAS lib_digipot7)



target_include_directories(lib_digipot7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digipot7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digipot7 PUBLIC MikroSDK.Driver)
