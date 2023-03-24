cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ldc1000 LANGUAGES MikroC)
else()
    project(lib_ldc1000 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ldc1000 STATIC
        src/ldc1000.c
        include/ldc1000.h
)
add_library(Click.Ldc1000  ALIAS lib_ldc1000)



target_include_directories(lib_ldc1000 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ldc1000 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ldc1000 PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})
