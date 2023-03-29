cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current LANGUAGES MikroC)
else()
    project(lib_current LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current STATIC
        src/current.c
        include/current.h
)
add_library(Click.Current  ALIAS lib_current)



target_include_directories(lib_current PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current PUBLIC MikroSDK.Driver)
