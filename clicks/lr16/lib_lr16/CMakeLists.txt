cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lr16 LANGUAGES MikroC)
else()
    project(lib_lr16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lr16 STATIC
        src/lr16.c
        include/lr16.h
)
add_library(Click.LR16  ALIAS lib_lr16)



target_include_directories(lib_lr16 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lr16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lr16 PUBLIC MikroSDK.Driver)

