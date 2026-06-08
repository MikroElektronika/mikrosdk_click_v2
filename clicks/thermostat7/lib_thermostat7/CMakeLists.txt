cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermostat7 LANGUAGES MikroC)
else()
    project(lib_thermostat7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermostat7 STATIC
        src/thermostat7.c
        include/thermostat7.h
)
add_library(Click.Thermostat7  ALIAS lib_thermostat7)



target_include_directories(lib_thermostat7 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermostat7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermostat7 PUBLIC MikroSDK.Driver)

