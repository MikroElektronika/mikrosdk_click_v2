cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gps4 LANGUAGES MikroC)
else()
    project(lib_gps4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gps4 STATIC
        src/gps4.c
        include/gps4.h
)
add_library(Click.Gps4  ALIAS lib_gps4)



target_include_directories(lib_gps4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gps4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gps4 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gps4 PUBLIC MikroSDK.GenericPointer)
