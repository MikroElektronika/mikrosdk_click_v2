cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_audioamp9 LANGUAGES MikroC)
else()
    project(lib_audioamp9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_audioamp9 STATIC
        src/audioamp9.c
        include/audioamp9.h
)
add_library(Click.AudioAmp9  ALIAS lib_audioamp9)



target_include_directories(lib_audioamp9 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_audioamp9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_audioamp9 PUBLIC MikroSDK.Driver)

