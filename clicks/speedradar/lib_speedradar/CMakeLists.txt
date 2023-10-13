cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_speedradar LANGUAGES MikroC)
else()
    project(lib_speedradar LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_speedradar STATIC
        src/speedradar.c
        include/speedradar.h
)
add_library(Click.SpeedRadar  ALIAS lib_speedradar)



target_include_directories(lib_speedradar PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_speedradar PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_speedradar PUBLIC MikroSDK.Driver)

