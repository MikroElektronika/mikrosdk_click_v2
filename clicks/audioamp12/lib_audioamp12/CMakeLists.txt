cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_audioamp12 LANGUAGES MikroC)
else()
    project(lib_audioamp12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_audioamp12 STATIC
        src/audioamp12.c
        include/audioamp12.h
)
add_library(Click.AudioAMP12  ALIAS lib_audioamp12)



target_include_directories(lib_audioamp12 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_audioamp12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_audioamp12 PUBLIC MikroSDK.Driver)

