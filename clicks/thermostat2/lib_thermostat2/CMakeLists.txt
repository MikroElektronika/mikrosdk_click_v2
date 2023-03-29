cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermostat2 LANGUAGES MikroC)
else()
    project(lib_thermostat2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermostat2 STATIC
        src/thermostat2.c
        include/thermostat2.h
)
add_library(Click.Thermostat2  ALIAS lib_thermostat2)



target_include_directories(lib_thermostat2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermostat2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermostat2 PUBLIC MikroSDK.Driver)
