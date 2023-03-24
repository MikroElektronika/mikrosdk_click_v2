cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pwm2 LANGUAGES MikroC)
else()
    project(lib_pwm2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pwm2 STATIC
        src/pwm2.c
        include/pwm2.h
)
add_library(Click.Pwm2  ALIAS lib_pwm2)



target_include_directories(lib_pwm2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pwm2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pwm2 PUBLIC MikroSDK.Driver)
