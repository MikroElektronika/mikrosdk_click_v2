cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tilt LANGUAGES MikroC)
else()
    project(lib_tilt LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tilt STATIC
        src/tilt.c
        include/tilt.h
)
add_library(Click.Tilt  ALIAS lib_tilt)



target_include_directories(lib_tilt PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tilt PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tilt PUBLIC MikroSDK.Driver)
