cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_alcohol3 LANGUAGES MikroC)
else()
    project(lib_alcohol3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_alcohol3 STATIC
        src/alcohol3.c
        include/alcohol3.h
)
add_library(Click.Alcohol3  ALIAS lib_alcohol3)



target_include_directories(lib_alcohol3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_alcohol3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_alcohol3 PUBLIC MikroSDK.Driver)
