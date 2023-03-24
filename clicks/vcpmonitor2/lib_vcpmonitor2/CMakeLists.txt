cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vcpmonitor2 LANGUAGES MikroC)
else()
    project(lib_vcpmonitor2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vcpmonitor2 STATIC
        src/vcpmonitor2.c
        include/vcpmonitor2.h
)
add_library(Click.Vcpmonitor2  ALIAS lib_vcpmonitor2)



target_include_directories(lib_vcpmonitor2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vcpmonitor2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vcpmonitor2 PUBLIC MikroSDK.Driver)
