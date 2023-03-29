cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_alcohol LANGUAGES MikroC)
else()
    project(lib_alcohol LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_alcohol STATIC
        src/alcohol.c
        include/alcohol.h
)
add_library(Click.Alcohol  ALIAS lib_alcohol)



target_include_directories(lib_alcohol PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_alcohol PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_alcohol PUBLIC MikroSDK.Driver)
