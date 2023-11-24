cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_piezodriver LANGUAGES MikroC)
else()
    project(lib_piezodriver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_piezodriver STATIC
        src/piezodriver.c
        include/piezodriver.h
)
add_library(Click.PiezoDriver  ALIAS lib_piezodriver)



target_include_directories(lib_piezodriver PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_piezodriver PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_piezodriver PUBLIC MikroSDK.Driver)

