cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irthermo5v LANGUAGES MikroC)
else()
    project(lib_irthermo5v LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irthermo5v STATIC
        src/irthermo5v.c
        include/irthermo5v.h
)
add_library(Click.IrThermo5V  ALIAS lib_irthermo5v)



target_include_directories(lib_irthermo5v PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irthermo5v PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irthermo5v PUBLIC MikroSDK.Driver)
