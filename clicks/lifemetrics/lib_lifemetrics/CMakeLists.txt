cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lifemetrics LANGUAGES MikroC)
else()
    project(lib_lifemetrics LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lifemetrics STATIC
        src/lifemetrics.c
        include/lifemetrics.h
)
add_library(Click.LifeMetrics  ALIAS lib_lifemetrics)



target_include_directories(lib_lifemetrics PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lifemetrics PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lifemetrics PUBLIC MikroSDK.Driver)

