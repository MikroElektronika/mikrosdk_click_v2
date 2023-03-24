cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_audioamp5 LANGUAGES MikroC)
else()
    project(lib_audioamp5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_audioamp5 STATIC
        src/audioamp5.c
        include/audioamp5.h
)
add_library(Click.AudioAmp5  ALIAS lib_audioamp5)



target_include_directories(lib_audioamp5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_audioamp5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_audioamp5 PUBLIC MikroSDK.Driver)
