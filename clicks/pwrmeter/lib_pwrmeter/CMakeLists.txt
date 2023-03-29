cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pwrmeter LANGUAGES MikroC)
else()
    project(lib_pwrmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pwrmeter STATIC
        src/pwrmeter.c
        include/pwrmeter.h
)
add_library(Click.PwrMeter  ALIAS lib_pwrmeter)



target_include_directories(lib_pwrmeter PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pwrmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pwrmeter PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
