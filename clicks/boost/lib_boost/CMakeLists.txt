cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_boost LANGUAGES MikroC)
else()
    project(lib_boost LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_boost STATIC
        src/boost.c
        include/boost.h
)
add_library(Click.Boost  ALIAS lib_boost)



target_include_directories(lib_boost PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_boost PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_boost PUBLIC MikroSDK.Driver)
