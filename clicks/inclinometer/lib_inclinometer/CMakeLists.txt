cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_inclinometer LANGUAGES MikroC)
else()
    project(lib_inclinometer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_inclinometer STATIC
        src/inclinometer.c
        include/inclinometer.h
)
add_library(Click.Inclinometer  ALIAS lib_inclinometer)



target_include_directories(lib_inclinometer PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_inclinometer PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_inclinometer PUBLIC MikroSDK.Driver)
