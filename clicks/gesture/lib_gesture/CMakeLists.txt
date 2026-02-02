cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gesture LANGUAGES MikroC)
else()
    project(lib_gesture LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gesture STATIC
        src/gesture.c
        include/gesture.h
)
add_library(Click.Gesture  ALIAS lib_gesture)



target_include_directories(lib_gesture PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gesture PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gesture PUBLIC MikroSDK.Driver)

