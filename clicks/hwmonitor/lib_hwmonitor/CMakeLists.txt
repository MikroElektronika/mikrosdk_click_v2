cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hwmonitor LANGUAGES MikroC)
else()
    project(lib_hwmonitor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hwmonitor STATIC
        src/hwmonitor.c
        include/hwmonitor.h
)
add_library(Click.HWMonitor  ALIAS lib_hwmonitor)



target_include_directories(lib_hwmonitor PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hwmonitor PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hwmonitor PUBLIC MikroSDK.Driver)

