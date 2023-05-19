cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_compass6 LANGUAGES MikroC)
else()
    project(lib_compass6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_compass6 STATIC
        src/compass6.c
        include/compass6.h
)
add_library(Click.Compass6  ALIAS lib_compass6)



target_include_directories(lib_compass6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_compass6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_compass6 PUBLIC MikroSDK.Driver)
