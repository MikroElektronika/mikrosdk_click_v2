cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_servo2 LANGUAGES MikroC)
else()
    project(lib_servo2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_servo2 STATIC
        src/servo2.c
        include/servo2.h
)
add_library(Click.Servo2  ALIAS lib_servo2)



target_include_directories(lib_servo2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_servo2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_servo2 PUBLIC MikroSDK.Driver)

