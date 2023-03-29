cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo6 LANGUAGES MikroC)
else()
    project(lib_thermo6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo6 STATIC
        src/thermo6.c
        include/thermo6.h
)
add_library(Click.Thermo6  ALIAS lib_thermo6)



target_include_directories(lib_thermo6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo6 PUBLIC MikroSDK.Driver)
