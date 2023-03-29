cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_radar LANGUAGES MikroC)
else()
    project(lib_radar LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_radar STATIC
        src/radar.c
        include/radar.h
)
add_library(Click.Radar  ALIAS lib_radar)



target_include_directories(lib_radar PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_radar PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_radar PUBLIC MikroSDK.Driver)
