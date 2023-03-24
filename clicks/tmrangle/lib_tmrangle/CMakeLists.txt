cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tmrangle LANGUAGES MikroC)
else()
    project(lib_tmrangle LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tmrangle STATIC
        src/tmrangle.c
        include/tmrangle.h
)
add_library(Click.TMRAngle  ALIAS lib_tmrangle)



target_include_directories(lib_tmrangle PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tmrangle PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tmrangle PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
