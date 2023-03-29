cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pwm LANGUAGES MikroC)
else()
    project(lib_pwm LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pwm STATIC
        src/pwm.c
        include/pwm.h
)
add_library(Click.Pwm  ALIAS lib_pwm)



target_include_directories(lib_pwm PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pwm PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pwm PUBLIC MikroSDK.Driver)
