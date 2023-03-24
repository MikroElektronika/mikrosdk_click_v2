cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_audioamp4 LANGUAGES MikroC)
else()
    project(lib_audioamp4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_audioamp4 STATIC
        src/audioamp4.c
        include/audioamp4.h
)
add_library(Click.AudioAmp4  ALIAS lib_audioamp4)



target_include_directories(lib_audioamp4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_audioamp4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_audioamp4 PUBLIC MikroSDK.Driver)
