cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel13 LANGUAGES MikroC)
else()
    project(lib_accel13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel13 STATIC
        src/accel13.c
        include/accel13.h
)
add_library(Click.Accel13  ALIAS lib_accel13)



target_include_directories(lib_accel13 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel13 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel13 PUBLIC MikroSDK.Driver)
