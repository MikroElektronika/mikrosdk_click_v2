cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lsm6dsl LANGUAGES MikroC)
else()
    project(lib_lsm6dsl LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lsm6dsl STATIC
        src/lsm6dsl.c
        include/lsm6dsl.h
)
add_library(Click.Lsm6Dsl  ALIAS lib_lsm6dsl)



target_include_directories(lib_lsm6dsl PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lsm6dsl PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lsm6dsl PUBLIC MikroSDK.Driver)
