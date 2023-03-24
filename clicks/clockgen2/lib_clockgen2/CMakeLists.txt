cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_clockgen2 LANGUAGES MikroC)
else()
    project(lib_clockgen2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_clockgen2 STATIC
        src/clockgen2.c
        include/clockgen2.h
)
add_library(Click.ClockGen2  ALIAS lib_clockgen2)



target_include_directories(lib_clockgen2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_clockgen2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_clockgen2 PUBLIC MikroSDK.Driver)
