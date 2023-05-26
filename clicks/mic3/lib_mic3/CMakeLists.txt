cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mic3 LANGUAGES MikroC)
else()
    project(lib_mic3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mic3 STATIC
        src/mic3.c
        include/mic3.h
)
add_library(Click.MIC3  ALIAS lib_mic3)



target_include_directories(lib_mic3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mic3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mic3 PUBLIC MikroSDK.Driver)
