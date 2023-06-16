cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure8 LANGUAGES MikroC)
else()
    project(lib_pressure8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure8 STATIC
        src/pressure8.c
        include/pressure8.h
)
add_library(Click.Pressure8  ALIAS lib_pressure8)



target_include_directories(lib_pressure8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure8 PUBLIC MikroSDK.Driver)
