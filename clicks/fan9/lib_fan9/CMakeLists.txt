cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_fan9 LANGUAGES MikroC)
else()
    project(lib_fan9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_fan9 STATIC
        src/fan9.c
        include/fan9.h
)
add_library(Click.Fan9  ALIAS lib_fan9)



target_include_directories(lib_fan9 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_fan9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_fan9 PUBLIC MikroSDK.Driver)

