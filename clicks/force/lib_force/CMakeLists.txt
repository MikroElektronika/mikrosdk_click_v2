cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_force LANGUAGES MikroC)
else()
    project(lib_force LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_force STATIC
        src/force.c
        include/force.h
)
add_library(Click.Force  ALIAS lib_force)



target_include_directories(lib_force PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_force PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_force PUBLIC MikroSDK.Driver)
