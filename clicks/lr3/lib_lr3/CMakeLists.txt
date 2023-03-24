cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lr3 LANGUAGES MikroC)
else()
    project(lib_lr3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lr3 STATIC
        src/lr3.c
        include/lr3.h
)
add_library(Click.LR3  ALIAS lib_lr3)



target_include_directories(lib_lr3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lr3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lr3 PUBLIC MikroSDK.Driver)
