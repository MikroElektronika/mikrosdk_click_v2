cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wifly LANGUAGES MikroC)
else()
    project(lib_wifly LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wifly STATIC
        src/wifly.c
        include/wifly.h
)
add_library(Click.WiFly  ALIAS lib_wifly)



target_include_directories(lib_wifly PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wifly PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wifly PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_wifly PUBLIC MikroSDK.Conversions)

