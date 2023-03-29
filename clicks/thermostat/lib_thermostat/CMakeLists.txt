cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermostat LANGUAGES MikroC)
else()
    project(lib_thermostat LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermostat STATIC
        src/thermostat.c
        include/thermostat.h
)
add_library(Click.Thermostat  ALIAS lib_thermostat)



target_include_directories(lib_thermostat PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermostat PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermostat PUBLIC MikroSDK.Driver)
