cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure16 LANGUAGES MikroC)
else()
    project(lib_pressure16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure16 STATIC
        src/pressure16.c
        include/pressure16.h
)
add_library(Click.Pressure16  ALIAS lib_pressure16)



target_include_directories(lib_pressure16 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure16 PUBLIC MikroSDK.Driver)
