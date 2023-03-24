cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lr4 LANGUAGES MikroC)
else()
    project(lib_lr4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lr4 STATIC
        src/lr4.c
        include/lr4.h
)
add_library(Click.LR4  ALIAS lib_lr4)



target_include_directories(lib_lr4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lr4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lr4 PUBLIC MikroSDK.Driver)
