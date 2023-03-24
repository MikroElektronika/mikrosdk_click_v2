cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_amrangle LANGUAGES MikroC)
else()
    project(lib_amrangle LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_amrangle STATIC
        src/amrangle.c
        include/amrangle.h
)
add_library(Click.AMRAngle  ALIAS lib_amrangle)



target_include_directories(lib_amrangle PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_amrangle PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_amrangle PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
