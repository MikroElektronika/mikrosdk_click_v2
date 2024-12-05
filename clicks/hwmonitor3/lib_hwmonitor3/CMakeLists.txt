cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hwmonitor3 LANGUAGES MikroC)
else()
    project(lib_hwmonitor3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hwmonitor3 STATIC
        src/hwmonitor3.c
        include/hwmonitor3.h
)
add_library(Click.HWMonitor3  ALIAS lib_hwmonitor3)



target_include_directories(lib_hwmonitor3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hwmonitor3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hwmonitor3 PUBLIC MikroSDK.Driver)

