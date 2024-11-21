cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vcpmonitor5 LANGUAGES MikroC)
else()
    project(lib_vcpmonitor5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vcpmonitor5 STATIC
        src/vcpmonitor5.c
        include/vcpmonitor5.h
)
add_library(Click.VCPMonitor5  ALIAS lib_vcpmonitor5)



target_include_directories(lib_vcpmonitor5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vcpmonitor5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vcpmonitor5 PUBLIC MikroSDK.Driver)

