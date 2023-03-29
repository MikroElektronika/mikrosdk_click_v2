cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_enocean LANGUAGES MikroC)
else()
    project(lib_enocean LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_enocean STATIC
        src/enocean.c
        include/enocean.h
)
add_library(Click.EnOcean  ALIAS lib_enocean)



target_include_directories(lib_enocean PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_enocean PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_enocean PUBLIC MikroSDK.Driver)
