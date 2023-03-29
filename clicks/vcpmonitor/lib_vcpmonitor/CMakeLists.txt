cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vcpmonitor LANGUAGES MikroC)
else()
    project(lib_vcpmonitor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vcpmonitor STATIC
        src/vcpmonitor.c
        include/vcpmonitor.h
)
add_library(Click.VCPmonitor  ALIAS lib_vcpmonitor)



target_include_directories(lib_vcpmonitor PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vcpmonitor PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vcpmonitor PUBLIC MikroSDK.Driver)
