cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gsmgps LANGUAGES MikroC)
else()
    project(lib_gsmgps LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gsmgps STATIC
        src/gsmgps.c
        include/gsmgps.h
)
add_library(Click.Gsmgps  ALIAS lib_gsmgps)



target_include_directories(lib_gsmgps PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gsmgps PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gsmgps PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gsmgps PUBLIC MikroSDK.GenericPointer)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_gsmgps PUBLIC MikroSDK.Conversions)
