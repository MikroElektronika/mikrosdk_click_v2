cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_microwave LANGUAGES MikroC)
else()
    project(lib_microwave LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_microwave STATIC
        src/microwave.c
        include/microwave.h
)
add_library(Click.Microwave  ALIAS lib_microwave)



target_include_directories(lib_microwave PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_microwave PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_microwave PUBLIC MikroSDK.Driver)
