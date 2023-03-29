cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dsp LANGUAGES MikroC)
else()
    project(lib_dsp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dsp STATIC
        src/dsp.c
        include/dsp.h
)
add_library(Click.Dsp  ALIAS lib_dsp)



target_include_directories(lib_dsp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dsp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dsp PUBLIC MikroSDK.Driver)
