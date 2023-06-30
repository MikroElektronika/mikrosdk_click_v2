cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_waveform LANGUAGES MikroC)
else()
    project(lib_waveform LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_waveform STATIC
        src/waveform.c
        include/waveform.h
)
add_library(Click.Waveform  ALIAS lib_waveform)



target_include_directories(lib_waveform PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_waveform PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_waveform PUBLIC MikroSDK.Driver)
