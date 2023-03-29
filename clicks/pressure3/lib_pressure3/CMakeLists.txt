cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pressure3 LANGUAGES MikroC)
else()
    project(lib_pressure3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pressure3 STATIC
        src/pressure3.c
        include/pressure3.h
)
add_library(Click.Pressure3  ALIAS lib_pressure3)



target_include_directories(lib_pressure3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pressure3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pressure3 PUBLIC MikroSDK.Driver)
