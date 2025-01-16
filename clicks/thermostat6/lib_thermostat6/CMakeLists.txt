cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermostat6 LANGUAGES MikroC)
else()
    project(lib_thermostat6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermostat6 STATIC
        src/thermostat6.c
        include/thermostat6.h
)
add_library(Click.Thermostat6  ALIAS lib_thermostat6)



target_include_directories(lib_thermostat6 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermostat6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermostat6 PUBLIC MikroSDK.Driver)

