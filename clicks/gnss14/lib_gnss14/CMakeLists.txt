cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnss14 LANGUAGES MikroC)
else()
    project(lib_gnss14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnss14 STATIC
        src/gnss14.c
        include/gnss14.h
)
add_library(Click.GNSS14  ALIAS lib_gnss14)



target_include_directories(lib_gnss14 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnss14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnss14 PUBLIC MikroSDK.Driver)

