cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo23 LANGUAGES MikroC)
else()
    project(lib_thermo23 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo23 STATIC
        src/thermo23.c
        include/thermo23.h
)
add_library(Click.Thermo23  ALIAS lib_thermo23)



target_include_directories(lib_thermo23 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo23 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo23 PUBLIC MikroSDK.Driver)
