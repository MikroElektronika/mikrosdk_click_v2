cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_batterysource LANGUAGES MikroC)
else()
    project(lib_batterysource LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_batterysource STATIC
        src/batterysource.c
        include/batterysource.h
)
add_library(Click.BatterySource  ALIAS lib_batterysource)



target_include_directories(lib_batterysource PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_batterysource PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_batterysource PUBLIC MikroSDK.Driver)

