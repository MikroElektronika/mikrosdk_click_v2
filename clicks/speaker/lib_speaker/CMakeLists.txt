cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_speaker LANGUAGES MikroC)
else()
    project(lib_speaker LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_speaker STATIC
        src/speaker.c
        include/speaker.h
)
add_library(Click.Speaker  ALIAS lib_speaker)



target_include_directories(lib_speaker PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_speaker PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_speaker PUBLIC MikroSDK.Driver)
