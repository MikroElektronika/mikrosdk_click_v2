cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_compass4 LANGUAGES MikroC)
else()
    project(lib_compass4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_compass4 STATIC
        src/compass4.c
        include/compass4.h
)
add_library(Click.Compass4  ALIAS lib_compass4)



target_include_directories(lib_compass4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_compass4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_compass4 PUBLIC MikroSDK.Driver)
