cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dac5 LANGUAGES MikroC)
else()
    project(lib_dac5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dac5 STATIC
        src/dac5.c
        include/dac5.h
)
add_library(Click.Dac5  ALIAS lib_dac5)



target_include_directories(lib_dac5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dac5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dac5 PUBLIC MikroSDK.Driver)
