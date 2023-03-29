cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dac LANGUAGES MikroC)
else()
    project(lib_dac LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dac STATIC
        src/dac.c
        include/dac.h
)
add_library(Click.Dac  ALIAS lib_dac)



target_include_directories(lib_dac PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dac PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dac PUBLIC MikroSDK.Driver)
