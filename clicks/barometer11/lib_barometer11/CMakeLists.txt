cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_barometer11 LANGUAGES MikroC)
else()
    project(lib_barometer11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_barometer11 STATIC
        src/barometer11.c
        include/barometer11.h
)
add_library(Click.Barometer11  ALIAS lib_barometer11)



target_include_directories(lib_barometer11 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_barometer11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_barometer11 PUBLIC MikroSDK.Driver)

