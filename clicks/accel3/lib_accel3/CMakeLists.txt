cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accel3 LANGUAGES MikroC)
else()
    project(lib_accel3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accel3 STATIC
        src/accel3.c
        include/accel3.h
)
add_library(Click.Accel3  ALIAS lib_accel3)



target_include_directories(lib_accel3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accel3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accel3 PUBLIC MikroSDK.Driver)
