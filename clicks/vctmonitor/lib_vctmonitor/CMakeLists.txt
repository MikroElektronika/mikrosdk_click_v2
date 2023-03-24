cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vctmonitor LANGUAGES MikroC)
else()
    project(lib_vctmonitor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vctmonitor STATIC
        src/vctmonitor.c
        include/vctmonitor.h
)
add_library(Click.VCTMonitor  ALIAS lib_vctmonitor)



target_include_directories(lib_vctmonitor PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vctmonitor PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vctmonitor PUBLIC MikroSDK.Driver)
