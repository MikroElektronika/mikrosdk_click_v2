cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_magneto7 LANGUAGES MikroC)
else()
    project(lib_magneto7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_magneto7 STATIC
        src/magneto7.c
        include/magneto7.h
)
add_library(Click.Magneto7  ALIAS lib_magneto7)



target_include_directories(lib_magneto7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_magneto7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_magneto7 PUBLIC MikroSDK.Driver)
