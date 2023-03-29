cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel24 LANGUAGES MikroC)
else()
    project(lib_accel24 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel24 STATIC
        src/accel24.c
        include/accel24.h
)
add_library(Click.Accel24  ALIAS lib_accel24)



target_include_directories(lib_accel24 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel24 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel24 PUBLIC MikroSDK.Driver)
