cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lr14 LANGUAGES MikroC)
else()
    project(lib_lr14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lr14 STATIC
        src/lr14.c
        include/lr14.h
)
add_library(Click.LR14  ALIAS lib_lr14)



target_include_directories(lib_lr14 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lr14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lr14 PUBLIC MikroSDK.Driver)

