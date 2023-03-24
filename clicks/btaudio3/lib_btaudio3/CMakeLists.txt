cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_btaudio3 LANGUAGES MikroC)
else()
    project(lib_btaudio3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_btaudio3 STATIC
        src/btaudio3.c
        include/btaudio3.h
)
add_library(Click.BTAudio3  ALIAS lib_btaudio3)



target_include_directories(lib_btaudio3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_btaudio3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_btaudio3 PUBLIC MikroSDK.Driver)
