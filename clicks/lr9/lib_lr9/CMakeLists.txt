cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lr9 LANGUAGES MikroC)
else()
    project(lib_lr9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lr9 STATIC
        src/lr9.c
        include/lr9.h
)
add_library(Click.LR9  ALIAS lib_lr9)



target_include_directories(lib_lr9 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lr9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lr9 PUBLIC MikroSDK.Driver)

