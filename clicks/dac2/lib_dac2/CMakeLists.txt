cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dac2 LANGUAGES MikroC)
else()
    project(lib_dac2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dac2 STATIC
        src/dac2.c
        include/dac2.h
)
add_library(Click.Dac2  ALIAS lib_dac2)



target_include_directories(lib_dac2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dac2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dac2 PUBLIC MikroSDK.Driver)
