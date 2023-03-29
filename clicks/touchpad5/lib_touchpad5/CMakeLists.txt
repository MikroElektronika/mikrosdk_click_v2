cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_touchpad5 LANGUAGES MikroC)
else()
    project(lib_touchpad5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_touchpad5 STATIC
        src/touchpad5.c
        include/touchpad5.h
)
add_library(Click.TouchPad5  ALIAS lib_touchpad5)



target_include_directories(lib_touchpad5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_touchpad5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_touchpad5 PUBLIC MikroSDK.Driver)
