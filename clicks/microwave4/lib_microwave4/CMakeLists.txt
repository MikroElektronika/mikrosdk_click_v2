cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_microwave4 LANGUAGES MikroC)
else()
    project(lib_microwave4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_microwave4 STATIC
        src/microwave4.c
        include/microwave4.h
)
add_library(Click.Microwave4  ALIAS lib_microwave4)



target_include_directories(lib_microwave4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_microwave4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_microwave4 PUBLIC MikroSDK.Driver)

