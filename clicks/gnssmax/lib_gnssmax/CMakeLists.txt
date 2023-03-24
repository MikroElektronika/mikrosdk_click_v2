cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnssmax LANGUAGES MikroC)
else()
    project(lib_gnssmax LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnssmax STATIC
        src/gnssmax.c
        include/gnssmax.h
)
add_library(Click.GNSSMAX  ALIAS lib_gnssmax)



target_include_directories(lib_gnssmax PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnssmax PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnssmax PUBLIC MikroSDK.Driver)
