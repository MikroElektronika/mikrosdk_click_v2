cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buckboost6 LANGUAGES MikroC)
else()
    project(lib_buckboost6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buckboost6 STATIC
        src/buckboost6.c
        include/buckboost6.h
)
add_library(Click.BuckBoost6  ALIAS lib_buckboost6)



target_include_directories(lib_buckboost6 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buckboost6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buckboost6 PUBLIC MikroSDK.Driver)

