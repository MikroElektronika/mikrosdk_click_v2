cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pwrmeter330a LANGUAGES MikroC)
else()
    project(lib_pwrmeter330a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pwrmeter330a STATIC
        src/pwrmeter330a.c
        include/pwrmeter330a.h
)
add_library(Click.PWRMeter330A  ALIAS lib_pwrmeter330a)



target_include_directories(lib_pwrmeter330a PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pwrmeter330a PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pwrmeter330a PUBLIC MikroSDK.Driver)
