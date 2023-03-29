cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity11 LANGUAGES MikroC)
else()
    project(lib_proximity11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity11 STATIC
        src/proximity11.c
        include/proximity11.h
)
add_library(Click.Proximity11  ALIAS lib_proximity11)



target_include_directories(lib_proximity11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity11 PUBLIC MikroSDK.Driver)
