cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_compass5 LANGUAGES MikroC)
else()
    project(lib_compass5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_compass5 STATIC
        src/compass5.c
        include/compass5.h
)
add_library(Click.Compass5  ALIAS lib_compass5)



target_include_directories(lib_compass5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_compass5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_compass5 PUBLIC MikroSDK.Driver)
