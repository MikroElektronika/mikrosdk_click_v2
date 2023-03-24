cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_audioamp6 LANGUAGES MikroC)
else()
    project(lib_audioamp6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_audioamp6 STATIC
        src/audioamp6.c
        include/audioamp6.h
)
add_library(Click.AudioAmp6  ALIAS lib_audioamp6)



target_include_directories(lib_audioamp6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_audioamp6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_audioamp6 PUBLIC MikroSDK.Driver)
