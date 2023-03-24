cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_spirit2 LANGUAGES MikroC)
else()
    project(lib_spirit2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_spirit2 STATIC
        src/spirit2.c
        include/spirit2.h
)
add_library(Click.SPIRIT2  ALIAS lib_spirit2)



target_include_directories(lib_spirit2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_spirit2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_spirit2 PUBLIC MikroSDK.Driver)
