cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel7 LANGUAGES MikroC)
else()
    project(lib_accel7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel7 STATIC
        src/accel7.c
        include/accel7.h
)
add_library(Click.Accel7  ALIAS lib_accel7)



target_include_directories(lib_accel7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel7 PUBLIC MikroSDK.Driver)
