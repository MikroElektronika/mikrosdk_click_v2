cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digipot9 LANGUAGES MikroC)
else()
    project(lib_digipot9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digipot9 STATIC
        src/digipot9.c
        include/digipot9.h
)
add_library(Click.DIGIPOT9  ALIAS lib_digipot9)



target_include_directories(lib_digipot9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digipot9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digipot9 PUBLIC MikroSDK.Driver)
