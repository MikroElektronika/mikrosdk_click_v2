cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_airquality12 LANGUAGES MikroC)
else()
    project(lib_airquality12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_airquality12 STATIC
        src/airquality12.c
        include/airquality12.h
)
add_library(Click.AirQuality12  ALIAS lib_airquality12)


target_include_directories(lib_airquality12 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_airquality12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_airquality12 PUBLIC MikroSDK.Driver)

