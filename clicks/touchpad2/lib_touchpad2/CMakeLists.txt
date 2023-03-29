cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_touchpad2 LANGUAGES MikroC)
else()
    project(lib_touchpad2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_touchpad2 STATIC
        src/touchpad2.c
        include/touchpad2.h
)
add_library(Click.TouchPad2  ALIAS lib_touchpad2)



target_include_directories(lib_touchpad2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_touchpad2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_touchpad2 PUBLIC MikroSDK.Driver)
