cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_clockgen LANGUAGES MikroC)
else()
    project(lib_clockgen LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_clockgen STATIC
        src/clockgen.c
        include/clockgen.h
)
add_library(Click.ClockGen  ALIAS lib_clockgen)



target_include_directories(lib_clockgen PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_clockgen PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_clockgen PUBLIC MikroSDK.Driver)
