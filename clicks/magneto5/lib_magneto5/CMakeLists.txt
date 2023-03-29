cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneto5 LANGUAGES MikroC)
else()
    project(lib_magneto5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneto5 STATIC
        src/magneto5.c
        include/magneto5.h
)
add_library(Click.Magneto5  ALIAS lib_magneto5)



target_include_directories(lib_magneto5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneto5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneto5 PUBLIC MikroSDK.Driver)
