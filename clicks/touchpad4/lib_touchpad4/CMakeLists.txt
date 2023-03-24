cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_touchpad4 LANGUAGES MikroC)
else()
    project(lib_touchpad4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_touchpad4 STATIC
        src/touchpad4.c
        include/touchpad4.h
)
add_library(Click.Touchpad4  ALIAS lib_touchpad4)



target_include_directories(lib_touchpad4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_touchpad4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_touchpad4 PUBLIC MikroSDK.Driver)
