cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_airquality7 LANGUAGES MikroC)
else()
    project(lib_airquality7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_airquality7 STATIC
        src/airquality7.c
        include/airquality7.h
)
add_library(Click.AirQuality7  ALIAS lib_airquality7)



target_include_directories(lib_airquality7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_airquality7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_airquality7 PUBLIC MikroSDK.Driver)
