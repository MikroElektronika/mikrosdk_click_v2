cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buttonr LANGUAGES MikroC)
else()
    project(lib_buttonr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buttonr STATIC
        src/buttonr.c
        include/buttonr.h
)
add_library(Click.ButtonR  ALIAS lib_buttonr)



target_include_directories(lib_buttonr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buttonr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buttonr PUBLIC MikroSDK.Driver)
