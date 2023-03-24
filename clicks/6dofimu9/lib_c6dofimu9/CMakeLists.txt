cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c6dofimu9 LANGUAGES MikroC)
else()
    project(lib_c6dofimu9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c6dofimu9 STATIC
        src/c6dofimu9.c
        include/c6dofimu9.h
)
add_library(Click.6DOFIMU9  ALIAS lib_c6dofimu9)



target_include_directories(lib_c6dofimu9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c6dofimu9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c6dofimu9 PUBLIC MikroSDK.Driver)
