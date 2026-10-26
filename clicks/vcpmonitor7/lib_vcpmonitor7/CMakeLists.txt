cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vcpmonitor7 LANGUAGES MikroC)
else()
    project(lib_vcpmonitor7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vcpmonitor7 STATIC
        src/vcpmonitor7.c
        include/vcpmonitor7.h
)
add_library(Click.VCPMonitor7  ALIAS lib_vcpmonitor7)



target_include_directories(lib_vcpmonitor7 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vcpmonitor7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vcpmonitor7 PUBLIC MikroSDK.Driver)

