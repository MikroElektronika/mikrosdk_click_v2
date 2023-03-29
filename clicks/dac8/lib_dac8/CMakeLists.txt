cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dac8 LANGUAGES MikroC)
else()
    project(lib_dac8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dac8 STATIC
        src/dac8.c
        include/dac8.h
)
add_library(Click.Dac8  ALIAS lib_dac8)



target_include_directories(lib_dac8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dac8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dac8 PUBLIC MikroSDK.Driver)
