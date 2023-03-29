cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel11 LANGUAGES MikroC)
else()
    project(lib_accel11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel11 STATIC
        src/accel11.c
        include/accel11.h
)
add_library(Click.Accel11  ALIAS lib_accel11)



target_include_directories(lib_accel11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel11 PUBLIC MikroSDK.Driver)
