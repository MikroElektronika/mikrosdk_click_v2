cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pwrmeter390a LANGUAGES MikroC)
else()
    project(lib_pwrmeter390a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pwrmeter390a STATIC
        src/pwrmeter390a.c
        include/pwrmeter390a.h
)
add_library(Click.PWRMeter390A  ALIAS lib_pwrmeter390a)



target_include_directories(lib_pwrmeter390a PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pwrmeter390a PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pwrmeter390a PUBLIC MikroSDK.Driver)
