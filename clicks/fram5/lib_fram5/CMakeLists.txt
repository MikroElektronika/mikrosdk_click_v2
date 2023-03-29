cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_fram5 LANGUAGES MikroC)
else()
    project(lib_fram5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_fram5 STATIC
        src/fram5.c
        include/fram5.h
)
add_library(Click.FRAM5  ALIAS lib_fram5)



target_include_directories(lib_fram5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_fram5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_fram5 PUBLIC MikroSDK.Driver)
