cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_servo LANGUAGES MikroC)
else()
    project(lib_servo LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_servo STATIC
        src/servo.c
        include/servo.h
)
add_library(Click.Servo  ALIAS lib_servo)



target_include_directories(lib_servo PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_servo PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_servo PUBLIC MikroSDK.Driver)
