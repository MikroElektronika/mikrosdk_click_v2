cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_capsense LANGUAGES MikroC)
else()
    project(lib_capsense LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_capsense STATIC
        src/capsense.c
        include/capsense.h
)
add_library(Click.CapSense  ALIAS lib_capsense)



target_include_directories(lib_capsense PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_capsense PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_capsense PUBLIC MikroSDK.Driver)
