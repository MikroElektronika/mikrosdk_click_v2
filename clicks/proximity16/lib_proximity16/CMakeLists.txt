cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proximity16 LANGUAGES MikroC)
else()
    project(lib_proximity16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proximity16
STATIC
src/proximity16.c
include/proximity16.h
include/firmware_buffers.h
)
add_library(Click.Proximity16  ALIAS lib_proximity16)



target_include_directories(lib_proximity16 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proximity16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proximity16 PUBLIC MikroSDK.Driver)
