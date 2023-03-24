cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lr LANGUAGES MikroC)
else()
    project(lib_lr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lr STATIC
        src/lr.c
        include/lr.h
)
add_library(Click.LR  ALIAS lib_lr)



target_include_directories(lib_lr PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lr PUBLIC MikroSDK.Driver)

