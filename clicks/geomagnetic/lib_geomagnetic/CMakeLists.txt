cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_geomagnetic LANGUAGES MikroC)
else()
    project(lib_geomagnetic LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_geomagnetic STATIC
        src/geomagnetic.c
        include/geomagnetic.h
)
add_library(Click.Geomagnetic  ALIAS lib_geomagnetic)



target_include_directories(lib_geomagnetic PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_geomagnetic PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_geomagnetic PUBLIC MikroSDK.Driver)
