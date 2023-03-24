cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_barometer LANGUAGES MikroC)
else()
    project(lib_barometer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_barometer STATIC
        src/barometer.c
        include/barometer.h
)
add_library(Click.Barometer  ALIAS lib_barometer)



target_include_directories(lib_barometer PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_barometer PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_barometer PUBLIC MikroSDK.Driver)
