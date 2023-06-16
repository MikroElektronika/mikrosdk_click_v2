cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure9 LANGUAGES MikroC)
else()
    project(lib_pressure9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure9 STATIC
        src/pressure9.c
        include/pressure9.h
)
add_library(Click.Pressure9  ALIAS lib_pressure9)



target_include_directories(lib_pressure9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure9 PUBLIC MikroSDK.Driver)
