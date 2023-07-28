cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mp3 LANGUAGES MikroC)
else()
    project(lib_mp3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mp3
STATIC
src/mp3.c
include/mp3.h
include/mp3_resources.h
)
add_library(Click.Mp3  ALIAS lib_mp3)



target_include_directories(lib_mp3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mp3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mp3 PUBLIC MikroSDK.Driver)
