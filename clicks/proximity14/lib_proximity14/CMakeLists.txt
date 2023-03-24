cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity14 LANGUAGES MikroC)
else()
    project(lib_proximity14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity14 STATIC
        src/proximity14.c
        include/proximity14.h
)
add_library(Click.Proximity14  ALIAS lib_proximity14)



target_include_directories(lib_proximity14 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity14 PUBLIC MikroSDK.Driver)
