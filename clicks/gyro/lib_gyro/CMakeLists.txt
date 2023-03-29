cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gyro LANGUAGES MikroC)
else()
    project(lib_gyro LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gyro STATIC
        src/gyro.c
        include/gyro.h
)
add_library(Click.Gyro  ALIAS lib_gyro)



target_include_directories(lib_gyro PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gyro PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gyro PUBLIC MikroSDK.Driver)
