cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo24 LANGUAGES MikroC)
else()
    project(lib_thermo24 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo24 STATIC
        src/thermo24.c
        include/thermo24.h
)
add_library(Click.Thermo24  ALIAS lib_thermo24)



target_include_directories(lib_thermo24 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo24 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo24 PUBLIC MikroSDK.Driver)
