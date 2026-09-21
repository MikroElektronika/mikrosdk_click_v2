cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermocouple LANGUAGES MikroC)
else()
    project(lib_thermocouple LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermocouple STATIC
        src/thermocouple.c
        include/thermocouple.h
)
add_library(Click.Thermocouple  ALIAS lib_thermocouple)



target_include_directories(lib_thermocouple PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermocouple PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermocouple PUBLIC MikroSDK.Driver)

