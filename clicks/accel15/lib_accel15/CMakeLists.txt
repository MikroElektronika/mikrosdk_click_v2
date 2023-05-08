cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel15 LANGUAGES MikroC)
else()
    project(lib_accel15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel15 STATIC
        src/accel15.c
        include/accel15.h
)
add_library(Click.Accel15  ALIAS lib_accel15)



target_include_directories(lib_accel15 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel15 PUBLIC MikroSDK.Driver)
