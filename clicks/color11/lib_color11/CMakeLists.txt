cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color11 LANGUAGES MikroC)
else()
    project(lib_color11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color11 STATIC
        src/color11.c
        include/color11.h
)
add_library(Click.Color11  ALIAS lib_color11)



target_include_directories(lib_color11 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color11 PUBLIC MikroSDK.Driver)

