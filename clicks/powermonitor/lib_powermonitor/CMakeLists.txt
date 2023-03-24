cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_powermonitor LANGUAGES MikroC)
else()
    project(lib_powermonitor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_powermonitor STATIC
        src/powermonitor.c
        include/powermonitor.h
)
add_library(Click.PowerMonitor  ALIAS lib_powermonitor)



target_include_directories(lib_powermonitor PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_powermonitor PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_powermonitor PUBLIC MikroSDK.Driver)
