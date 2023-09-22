cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_apc1sensor LANGUAGES MikroC)
else()
    project(lib_apc1sensor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_apc1sensor STATIC
        src/apc1sensor.c
        include/apc1sensor.h
)
add_library(Click.APC1Sensor  ALIAS lib_apc1sensor)



target_include_directories(lib_apc1sensor PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_apc1sensor PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_apc1sensor PUBLIC MikroSDK.Driver)

