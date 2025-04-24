cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnss21 LANGUAGES MikroC)
else()
    project(lib_gnss21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnss21 STATIC
        src/gnss21.c
        include/gnss21.h
)
add_library(Click.GNSS21  ALIAS lib_gnss21)



target_include_directories(lib_gnss21 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnss21 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnss21 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnss21 PUBLIC MikroSDK.GenericPointer)

