cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel34 LANGUAGES MikroC)
else()
    project(lib_accel34 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel34 STATIC
        src/accel34.c
        include/accel34.h
)
add_library(Click.Accel34  ALIAS lib_accel34)



target_include_directories(lib_accel34 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel34 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel34 PUBLIC MikroSDK.Driver)

