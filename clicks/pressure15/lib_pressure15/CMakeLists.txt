cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure15 LANGUAGES MikroC)
else()
    project(lib_pressure15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure15 STATIC
        src/pressure15.c
        include/pressure15.h
)
add_library(Click.Pressure15  ALIAS lib_pressure15)



target_include_directories(lib_pressure15 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure15 PUBLIC MikroSDK.Driver)
