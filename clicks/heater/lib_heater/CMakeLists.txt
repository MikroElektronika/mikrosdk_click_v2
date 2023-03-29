cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_heater LANGUAGES MikroC)
else()
    project(lib_heater LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_heater STATIC
        src/heater.c
        include/heater.h
)
add_library(Click.Heater  ALIAS lib_heater)



target_include_directories(lib_heater PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_heater PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_heater PUBLIC MikroSDK.Driver)
