cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_altitude3 LANGUAGES MikroC)
else()
    project(lib_altitude3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_altitude3 STATIC
        src/altitude3.c
        include/altitude3.h
)
add_library(Click.Altitude3  ALIAS lib_altitude3)



target_include_directories(lib_altitude3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_altitude3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_altitude3 PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
