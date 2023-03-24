cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo8 LANGUAGES MikroC)
else()
    project(lib_thermo8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo8 STATIC
        src/thermo8.c
        include/thermo8.h
)
add_library(Click.Thermo8  ALIAS lib_thermo8)



target_include_directories(lib_thermo8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo8 PUBLIC MikroSDK.Driver)
