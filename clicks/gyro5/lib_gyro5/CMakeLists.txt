cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gyro5 LANGUAGES MikroC)
else()
    project(lib_gyro5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gyro5 STATIC
        src/gyro5.c
        include/gyro5.h
)
add_library(Click.Gyro5  ALIAS lib_gyro5)



target_include_directories(lib_gyro5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gyro5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gyro5 PUBLIC MikroSDK.Driver)
