cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digipot4 LANGUAGES MikroC)
else()
    project(lib_digipot4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digipot4 STATIC
        src/digipot4.c
        include/digipot4.h
)
add_library(Click.DigiPot4  ALIAS lib_digipot4)



target_include_directories(lib_digipot4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digipot4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digipot4 PUBLIC MikroSDK.Driver)
