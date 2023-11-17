cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c2x2rgb LANGUAGES MikroC)
else()
    project(lib_c2x2rgb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c2x2rgb STATIC
        src/c2x2rgb.c
        include/c2x2rgb.h
)
add_library(Click.2x2RGB  ALIAS lib_c2x2rgb)



target_include_directories(lib_c2x2rgb PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c2x2rgb PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c2x2rgb PUBLIC MikroSDK.Driver)

