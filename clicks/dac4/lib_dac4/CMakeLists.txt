cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dac4 LANGUAGES MikroC)
else()
    project(lib_dac4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dac4 STATIC
        src/dac4.c
        include/dac4.h
)
add_library(Click.Dac4  ALIAS lib_dac4)



target_include_directories(lib_dac4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dac4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dac4 PUBLIC MikroSDK.Driver)
