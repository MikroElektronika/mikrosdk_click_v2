cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_b102c LANGUAGES MikroC)
else()
    project(lib_b102c LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_b102c STATIC
        src/b102c.c
        include/b102c.h
)
add_library(Click.B102C  ALIAS lib_b102c)



target_include_directories(lib_b102c PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_b102c PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_b102c PUBLIC MikroSDK.Driver)

