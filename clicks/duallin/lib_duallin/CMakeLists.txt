cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_duallin LANGUAGES MikroC)
else()
    project(lib_duallin LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_duallin STATIC
        src/duallin.c
        include/duallin.h
)
add_library(Click.DualLin  ALIAS lib_duallin)



target_include_directories(lib_duallin PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_duallin PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_duallin PUBLIC MikroSDK.Driver)
