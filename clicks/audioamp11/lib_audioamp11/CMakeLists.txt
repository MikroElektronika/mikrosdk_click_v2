cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_audioamp11 LANGUAGES MikroC)
else()
    project(lib_audioamp11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_audioamp11 STATIC
        src/audioamp11.c
        include/audioamp11.h
)
add_library(Click.AudioAMP11  ALIAS lib_audioamp11)



target_include_directories(lib_audioamp11 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_audioamp11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_audioamp11 PUBLIC MikroSDK.Driver)

