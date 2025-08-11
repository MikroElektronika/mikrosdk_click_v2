cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_btaudio4 LANGUAGES MikroC)
else()
    project(lib_btaudio4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_btaudio4 STATIC
        src/btaudio4.c
        include/btaudio4.h
)
add_library(Click.BTAudio4  ALIAS lib_btaudio4)



target_include_directories(lib_btaudio4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_btaudio4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_btaudio4 PUBLIC MikroSDK.Driver)

