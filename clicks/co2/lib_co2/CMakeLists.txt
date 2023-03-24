cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_co2 LANGUAGES MikroC)
else()
    project(lib_co2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_co2 STATIC
        src/co2.c
        include/co2.h
)
add_library(Click.CO2  ALIAS lib_co2)



target_include_directories(lib_co2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_co2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_co2 PUBLIC MikroSDK.Driver)
