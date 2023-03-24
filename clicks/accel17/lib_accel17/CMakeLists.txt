cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel17 LANGUAGES MikroC)
else()
    project(lib_accel17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel17 STATIC
        src/accel17.c
        include/accel17.h
)
add_library(Click.Accel17  ALIAS lib_accel17)



target_include_directories(lib_accel17 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel17 PUBLIC MikroSDK.Driver)
