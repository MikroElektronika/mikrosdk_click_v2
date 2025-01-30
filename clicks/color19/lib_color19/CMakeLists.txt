cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color19 LANGUAGES MikroC)
else()
    project(lib_color19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color19 STATIC
        src/color19.c
        include/color19.h
)
add_library(Click.Color19  ALIAS lib_color19)



target_include_directories(lib_color19 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color19 PUBLIC MikroSDK.Driver)

