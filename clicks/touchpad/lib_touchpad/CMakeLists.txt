cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_touchpad LANGUAGES MikroC)
else()
    project(lib_touchpad LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_touchpad STATIC
        src/touchpad.c
        include/touchpad.h
)
add_library(Click.Touchpad  ALIAS lib_touchpad)



target_include_directories(lib_touchpad PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_touchpad PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_touchpad PUBLIC MikroSDK.Driver)
