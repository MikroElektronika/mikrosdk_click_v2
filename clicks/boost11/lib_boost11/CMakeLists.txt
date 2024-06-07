cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_boost11 LANGUAGES MikroC)
else()
    project(lib_boost11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_boost11 STATIC
        src/boost11.c
        include/boost11.h
)
add_library(Click.Boost11  ALIAS lib_boost11)



target_include_directories(lib_boost11 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_boost11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_boost11 PUBLIC MikroSDK.Driver)

