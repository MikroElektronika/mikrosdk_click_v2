cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_geomagnetic2 LANGUAGES MikroC)
else()
    project(lib_geomagnetic2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_geomagnetic2 STATIC
        src/geomagnetic2.c
        include/geomagnetic2.h
)
add_library(Click.GeoMagnetic2  ALIAS lib_geomagnetic2)



target_include_directories(lib_geomagnetic2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_geomagnetic2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_geomagnetic2 PUBLIC MikroSDK.Driver)

