cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_methane LANGUAGES MikroC)
else()
    project(lib_methane LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_methane STATIC
        src/methane.c
        include/methane.h
)
add_library(Click.Methane  ALIAS lib_methane)



target_include_directories(lib_methane PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_methane PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_methane PUBLIC MikroSDK.Driver)
