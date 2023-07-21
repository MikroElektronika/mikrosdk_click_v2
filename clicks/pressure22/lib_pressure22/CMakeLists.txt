cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure22 LANGUAGES MikroC)
else()
    project(lib_pressure22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure22 STATIC
        src/pressure22.c
        include/pressure22.h
)
add_library(Click.Pressure22  ALIAS lib_pressure22)



target_include_directories(lib_pressure22 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure22 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure22 PUBLIC MikroSDK.Driver)

