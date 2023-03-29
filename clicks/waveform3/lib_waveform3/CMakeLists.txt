cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_waveform3 LANGUAGES MikroC)
else()
    project(lib_waveform3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_waveform3 STATIC
        src/waveform3.c
        include/waveform3.h
)
add_library(Click.Waveform3  ALIAS lib_waveform3)



target_include_directories(lib_waveform3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_waveform3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_waveform3 PUBLIC MikroSDK.Driver)
