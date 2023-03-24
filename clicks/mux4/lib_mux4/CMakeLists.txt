cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mux4 LANGUAGES MikroC)
else()
    project(lib_mux4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mux4 STATIC
        src/mux4.c
        include/mux4.h
)
add_library(Click.MUX4  ALIAS lib_mux4)



target_include_directories(lib_mux4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mux4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mux4 PUBLIC MikroSDK.Driver)
