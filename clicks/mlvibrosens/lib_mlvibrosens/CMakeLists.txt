cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mlvibrosens LANGUAGES MikroC)
else()
    project(lib_mlvibrosens LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mlvibrosens STATIC
        src/mlvibrosens.c
        include/mlvibrosens.h
)
add_library(Click.MLVibroSens  ALIAS lib_mlvibrosens)



target_include_directories(lib_mlvibrosens PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mlvibrosens PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mlvibrosens PUBLIC MikroSDK.Driver)

