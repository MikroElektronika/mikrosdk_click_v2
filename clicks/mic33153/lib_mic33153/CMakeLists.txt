cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mic33153 LANGUAGES MikroC)
else()
    project(lib_mic33153 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mic33153 STATIC
        src/mic33153.c
        include/mic33153.h
)
add_library(Click.Mic33153  ALIAS lib_mic33153)



target_include_directories(lib_mic33153 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mic33153 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mic33153 PUBLIC MikroSDK.Driver)
