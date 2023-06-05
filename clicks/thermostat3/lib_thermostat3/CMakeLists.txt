cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermostat3 LANGUAGES MikroC)
else()
    project(lib_thermostat3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermostat3 STATIC
        src/thermostat3.c
        include/thermostat3.h
)
add_library(Click.Thermostat3  ALIAS lib_thermostat3)



target_include_directories(lib_thermostat3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermostat3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermostat3 PUBLIC MikroSDK.Driver)
