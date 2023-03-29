cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mic2 LANGUAGES MikroC)
else()
    project(lib_mic2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mic2 STATIC
        src/mic2.c
        include/mic2.h
)
add_library(Click.Mic2  ALIAS lib_mic2)



target_include_directories(lib_mic2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mic2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mic2 PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
