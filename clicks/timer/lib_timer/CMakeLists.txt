cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_timer LANGUAGES MikroC)
else()
    project(lib_timer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_timer STATIC
        src/timer.c
        include/timer.h
)
add_library(Click.Timer  ALIAS lib_timer)



target_include_directories(lib_timer PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_timer PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_timer PUBLIC MikroSDK.Driver)
