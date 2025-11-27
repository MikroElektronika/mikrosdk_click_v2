cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color21 LANGUAGES MikroC)
else()
    project(lib_color21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color21 STATIC
        src/color21.c
        include/color21.h
)
add_library(Click.Color21  ALIAS lib_color21)



target_include_directories(lib_color21 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color21 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color21 PUBLIC MikroSDK.Driver)

