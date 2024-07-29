cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ltecat13ex LANGUAGES MikroC)
else()
    project(lib_ltecat13ex LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ltecat13ex STATIC
        src/ltecat13ex.c
        include/ltecat13ex.h
)
add_library(Click.LTECat13EX  ALIAS lib_ltecat13ex)



target_include_directories(lib_ltecat13ex PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ltecat13ex PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ltecat13ex PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_ltecat13ex PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_ltecat13ex PUBLIC MikroSDK.GenericPointer)
