cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneto4 LANGUAGES MikroC)
else()
    project(lib_magneto4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneto4 STATIC
        src/magneto4.c
        include/magneto4.h
)
add_library(Click.Magneto4  ALIAS lib_magneto4)



target_include_directories(lib_magneto4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneto4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneto4 PUBLIC MikroSDK.Driver)
