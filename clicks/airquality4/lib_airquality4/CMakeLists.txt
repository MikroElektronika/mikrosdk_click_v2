cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_airquality4 LANGUAGES MikroC)
else()
    project(lib_airquality4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_airquality4 STATIC
        src/airquality4.c
        include/airquality4.h
)
add_library(Click.AirQuality4  ALIAS lib_airquality4)



target_include_directories(lib_airquality4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_airquality4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_airquality4 PUBLIC MikroSDK.Driver)
