cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_spirit LANGUAGES MikroC)
else()
    project(lib_spirit LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_spirit STATIC
        src/spirit.c
        include/spirit.h
)
add_library(Click.SPIRIT  ALIAS lib_spirit)



target_include_directories(lib_spirit PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_spirit PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_spirit PUBLIC MikroSDK.Driver)
