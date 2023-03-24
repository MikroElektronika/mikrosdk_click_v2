cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tilt2 LANGUAGES MikroC)
else()
    project(lib_tilt2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tilt2 STATIC
        src/tilt2.c
        include/tilt2.h
)
add_library(Click.Tilt2  ALIAS lib_tilt2)



target_include_directories(lib_tilt2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tilt2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tilt2 PUBLIC MikroSDK.Driver)
