cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel6 LANGUAGES MikroC)
else()
    project(lib_accel6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel6 STATIC
        src/accel6.c
        include/accel6.h
)
add_library(Click.Accel6  ALIAS lib_accel6)



target_include_directories(lib_accel6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel6 PUBLIC MikroSDK.Driver)
