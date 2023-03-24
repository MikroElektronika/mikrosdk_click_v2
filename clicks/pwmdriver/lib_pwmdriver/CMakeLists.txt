cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pwmdriver LANGUAGES MikroC)
else()
    project(lib_pwmdriver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pwmdriver STATIC
        src/pwmdriver.c
        include/pwmdriver.h
)
add_library(Click.PwmDriver  ALIAS lib_pwmdriver)



target_include_directories(lib_pwmdriver PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pwmdriver PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pwmdriver PUBLIC MikroSDK.Driver)
