cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_speedsense LANGUAGES MikroC)
else()
    project(lib_speedsense LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_speedsense STATIC
        src/speedsense.c
        include/speedsense.h
)
add_library(Click.SpeedSense  ALIAS lib_speedsense)



target_include_directories(lib_speedsense PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_speedsense PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_speedsense PUBLIC MikroSDK.Driver)

