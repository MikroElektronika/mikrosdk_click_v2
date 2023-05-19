cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bucknboost LANGUAGES MikroC)
else()
    project(lib_bucknboost LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bucknboost STATIC
        src/bucknboost.c
        include/bucknboost.h
)
add_library(Click.BucknBoost  ALIAS lib_bucknboost)



target_include_directories(lib_bucknboost PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bucknboost PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bucknboost PUBLIC MikroSDK.Driver)
