cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure13 LANGUAGES MikroC)
else()
    project(lib_pressure13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure13 STATIC
        src/pressure13.c
        include/pressure13.h
)
add_library(Click.Pressure13  ALIAS lib_pressure13)



target_include_directories(lib_pressure13 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure13 PUBLIC MikroSDK.Driver)
