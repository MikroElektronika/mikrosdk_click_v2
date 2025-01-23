cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lr15 LANGUAGES MikroC)
else()
    project(lib_lr15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lr15 STATIC
        src/lr15.c
        include/lr15.h
)
add_library(Click.LR15  ALIAS lib_lr15)



target_include_directories(lib_lr15 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lr15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lr15 PUBLIC MikroSDK.Driver)

