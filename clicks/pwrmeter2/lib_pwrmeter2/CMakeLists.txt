cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pwrmeter2 LANGUAGES MikroC)
else()
    project(lib_pwrmeter2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pwrmeter2 STATIC
        src/pwrmeter2.c
        include/pwrmeter2.h
)
add_library(Click.PwrMeter2  ALIAS lib_pwrmeter2)



target_include_directories(lib_pwrmeter2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pwrmeter2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pwrmeter2 PUBLIC MikroSDK.Driver)
