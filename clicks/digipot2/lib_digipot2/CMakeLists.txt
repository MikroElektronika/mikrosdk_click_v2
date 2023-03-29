cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digipot2 LANGUAGES MikroC)
else()
    project(lib_digipot2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digipot2 STATIC
        src/digipot2.c
        include/digipot2.h
)
add_library(Click.DigiPot2  ALIAS lib_digipot2)



target_include_directories(lib_digipot2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digipot2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digipot2 PUBLIC MikroSDK.Driver)
