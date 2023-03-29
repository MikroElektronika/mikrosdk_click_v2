cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mic24045 LANGUAGES MikroC)
else()
    project(lib_mic24045 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mic24045 STATIC
        src/mic24045.c
        include/mic24045.h
)
add_library(Click.Mic24045  ALIAS lib_mic24045)



target_include_directories(lib_mic24045 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mic24045 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mic24045 PUBLIC MikroSDK.Driver)
