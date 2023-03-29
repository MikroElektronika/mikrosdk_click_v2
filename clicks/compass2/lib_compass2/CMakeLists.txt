cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_compass2 LANGUAGES MikroC)
else()
    project(lib_compass2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_compass2 STATIC
        src/compass2.c
        include/compass2.h
)
add_library(Click.Compass2  ALIAS lib_compass2)



target_include_directories(lib_compass2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_compass2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_compass2 PUBLIC MikroSDK.Driver)
