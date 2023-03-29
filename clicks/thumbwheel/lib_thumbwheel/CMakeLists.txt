cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thumbwheel LANGUAGES MikroC)
else()
    project(lib_thumbwheel LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thumbwheel STATIC
        src/thumbwheel.c
        include/thumbwheel.h
)
add_library(Click.Thumbwheel  ALIAS lib_thumbwheel)



target_include_directories(lib_thumbwheel PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thumbwheel PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thumbwheel PUBLIC MikroSDK.Driver)
