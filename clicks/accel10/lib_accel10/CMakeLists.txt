cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel10 LANGUAGES MikroC)
else()
    project(lib_accel10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel10 STATIC
        src/accel10.c
        include/accel10.h
)
add_library(Click.Accel10  ALIAS lib_accel10)



target_include_directories(lib_accel10 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel10 PUBLIC MikroSDK.Driver)
