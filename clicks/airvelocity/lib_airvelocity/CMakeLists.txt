cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_airvelocity LANGUAGES MikroC)
else()
    project(lib_airvelocity LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_airvelocity STATIC
        src/airvelocity.c
        include/airvelocity.h
)
add_library(Click.AirVelocity  ALIAS lib_airvelocity)



target_include_directories(lib_airvelocity PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_airvelocity PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_airvelocity PUBLIC MikroSDK.Driver)
