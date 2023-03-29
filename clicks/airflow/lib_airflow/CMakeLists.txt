cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_airflow LANGUAGES MikroC)
else()
    project(lib_airflow LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_airflow STATIC
        src/airflow.c
        include/airflow.h
)
add_library(Click.AirFlow  ALIAS lib_airflow)



target_include_directories(lib_airflow PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_airflow PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_airflow PUBLIC MikroSDK.Driver)
