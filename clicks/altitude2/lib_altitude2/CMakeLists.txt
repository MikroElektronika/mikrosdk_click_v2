cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_altitude2 LANGUAGES MikroC)
else()
    project(lib_altitude2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_altitude2 STATIC
        src/altitude2.c
        include/altitude2.h
)
add_library(Click.Altitude2  ALIAS lib_altitude2)



target_include_directories(lib_altitude2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_altitude2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_altitude2 PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
