cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure LANGUAGES MikroC)
else()
    project(lib_pressure LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure STATIC
        src/pressure.c
        include/pressure.h
)
add_library(Click.Pressure  ALIAS lib_pressure)



target_include_directories(lib_pressure PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure PUBLIC MikroSDK.Driver)
