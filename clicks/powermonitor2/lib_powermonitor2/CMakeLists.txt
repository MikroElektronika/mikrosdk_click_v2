cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_powermonitor2 LANGUAGES MikroC)
else()
    project(lib_powermonitor2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_powermonitor2 STATIC
        src/powermonitor2.c
        include/powermonitor2.h
)
add_library(Click.PowerMonitor2  ALIAS lib_powermonitor2)



target_include_directories(lib_powermonitor2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_powermonitor2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_powermonitor2 PUBLIC MikroSDK.Driver)

