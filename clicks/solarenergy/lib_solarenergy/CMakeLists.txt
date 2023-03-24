cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_solarenergy LANGUAGES MikroC)
else()
    project(lib_solarenergy LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_solarenergy STATIC
        src/solarenergy.c
        include/solarenergy.h
)
add_library(Click.SolarEnergy  ALIAS lib_solarenergy)



target_include_directories(lib_solarenergy PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_solarenergy PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_solarenergy PUBLIC MikroSDK.Driver)
