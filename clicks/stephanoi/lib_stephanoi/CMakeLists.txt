cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stephanoi LANGUAGES MikroC)
else()
    project(lib_stephanoi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stephanoi STATIC
        src/stephanoi.c
        include/stephanoi.h
)
add_library(Click.StephanoI  ALIAS lib_stephanoi)



target_include_directories(lib_stephanoi PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stephanoi PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stephanoi PUBLIC MikroSDK.Driver)

