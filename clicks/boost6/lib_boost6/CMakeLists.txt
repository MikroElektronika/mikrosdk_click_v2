cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_boost6 LANGUAGES MikroC)
else()
    project(lib_boost6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_boost6 STATIC
        src/boost6.c
        include/boost6.h
)
add_library(Click.Boost6  ALIAS lib_boost6)



target_include_directories(lib_boost6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_boost6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_boost6 PUBLIC MikroSDK.Driver)
