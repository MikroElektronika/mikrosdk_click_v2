cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gyro4 LANGUAGES MikroC)
else()
    project(lib_gyro4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gyro4 STATIC
        src/gyro4.c
        include/gyro4.h
)
add_library(Click.Gyro4  ALIAS lib_gyro4)



target_include_directories(lib_gyro4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gyro4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gyro4 PUBLIC MikroSDK.Driver)
