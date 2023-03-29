cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vacuum LANGUAGES MikroC)
else()
    project(lib_vacuum LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vacuum STATIC
        src/vacuum.c
        include/vacuum.h
)
add_library(Click.Vacuum  ALIAS lib_vacuum)



target_include_directories(lib_vacuum PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vacuum PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vacuum PUBLIC MikroSDK.Driver)
