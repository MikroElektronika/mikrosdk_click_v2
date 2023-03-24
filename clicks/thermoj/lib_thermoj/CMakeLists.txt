cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermoj LANGUAGES MikroC)
else()
    project(lib_thermoj LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermoj STATIC
        src/thermoj.c
        include/thermoj.h
)
add_library(Click.ThermoJ  ALIAS lib_thermoj)



target_include_directories(lib_thermoj PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermoj PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermoj PUBLIC MikroSDK.Driver)
