cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_terminal LANGUAGES MikroC)
else()
    project(lib_terminal LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_terminal STATIC
        src/terminal.c
        include/terminal.h
)
add_library(Click.Terminal  ALIAS lib_terminal)



target_include_directories(lib_terminal PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_terminal PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_terminal PUBLIC MikroSDK.Driver)
