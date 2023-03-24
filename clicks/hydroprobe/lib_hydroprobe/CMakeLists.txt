cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hydroprobe LANGUAGES MikroC)
else()
    project(lib_hydroprobe LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hydroprobe STATIC
        src/hydroprobe.c
        include/hydroprobe.h
)
add_library(Click.HydroProbe  ALIAS lib_hydroprobe)



target_include_directories(lib_hydroprobe PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hydroprobe PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hydroprobe PUBLIC MikroSDK.Driver)
