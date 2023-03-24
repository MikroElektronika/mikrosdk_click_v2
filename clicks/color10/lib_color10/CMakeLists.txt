cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_color10 LANGUAGES MikroC)
else()
    project(lib_color10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_color10 STATIC
        src/color10.c
        include/color10.h
)
add_library(Click.Color10  ALIAS lib_color10)



target_include_directories(lib_color10 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_color10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_color10 PUBLIC MikroSDK.Driver)
