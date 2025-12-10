cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dac21 LANGUAGES MikroC)
else()
    project(lib_dac21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dac21 STATIC
        src/dac21.c
        include/dac21.h
)
add_library(Click.DAC21  ALIAS lib_dac21)



target_include_directories(lib_dac21 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dac21 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dac21 PUBLIC MikroSDK.Driver)

