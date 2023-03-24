cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermok LANGUAGES MikroC)
else()
    project(lib_thermok LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermok STATIC
        src/thermok.c
        include/thermok.h
)
add_library(Click.ThermoK  ALIAS lib_thermok)



target_include_directories(lib_thermok PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermok PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermok PUBLIC MikroSDK.Driver)
