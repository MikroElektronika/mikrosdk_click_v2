cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pwrmeter3 LANGUAGES MikroC)
else()
    project(lib_pwrmeter3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pwrmeter3 STATIC
        src/pwrmeter3.c
        include/pwrmeter3.h
)
add_library(Click.PWRMeter3  ALIAS lib_pwrmeter3)



target_include_directories(lib_pwrmeter3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pwrmeter3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pwrmeter3 PUBLIC MikroSDK.Driver)
