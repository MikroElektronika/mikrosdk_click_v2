cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_moisture LANGUAGES MikroC)
else()
    project(lib_moisture LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_moisture STATIC
        src/moisture.c
        include/moisture.h
)
add_library(Click.Moisture  ALIAS lib_moisture)



target_include_directories(lib_moisture PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_moisture PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_moisture PUBLIC MikroSDK.Driver)
