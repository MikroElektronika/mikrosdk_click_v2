cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dac7 LANGUAGES MikroC)
else()
    project(lib_dac7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dac7 STATIC
        src/dac7.c
        include/dac7.h
)
add_library(Click.Dac7  ALIAS lib_dac7)



target_include_directories(lib_dac7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dac7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dac7 PUBLIC MikroSDK.Driver)
