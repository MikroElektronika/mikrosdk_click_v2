cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity2 LANGUAGES MikroC)
else()
    project(lib_proximity2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity2 STATIC
        src/proximity2.c
        include/proximity2.h
)
add_library(Click.Proximity2  ALIAS lib_proximity2)



target_include_directories(lib_proximity2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity2 PUBLIC MikroSDK.Driver)
