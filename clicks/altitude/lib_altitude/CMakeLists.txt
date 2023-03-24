cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_altitude LANGUAGES MikroC)
else()
    project(lib_altitude LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_altitude STATIC
        src/altitude.c
        include/altitude.h
)
add_library(Click.Altitude  ALIAS lib_altitude)



target_include_directories(lib_altitude PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_altitude PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_altitude PUBLIC MikroSDK.Driver)
