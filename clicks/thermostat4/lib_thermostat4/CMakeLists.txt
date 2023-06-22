cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermostat4 LANGUAGES MikroC)
else()
    project(lib_thermostat4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermostat4 STATIC
        src/thermostat4.c
        include/thermostat4.h
)
add_library(Click.Thermostat4  ALIAS lib_thermostat4)



target_include_directories(lib_thermostat4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermostat4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermostat4 PUBLIC MikroSDK.Driver)
