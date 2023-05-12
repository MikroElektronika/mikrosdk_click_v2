cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_battman3 LANGUAGES MikroC)
else()
    project(lib_battman3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_battman3 STATIC
        src/battman3.c
        include/battman3.h
)
add_library(Click.BATT-MAN3  ALIAS lib_battman3)



target_include_directories(lib_battman3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_battman3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_battman3 PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
