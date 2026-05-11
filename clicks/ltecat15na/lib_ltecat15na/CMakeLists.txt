cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ltecat15na LANGUAGES MikroC)
else()
    project(lib_ltecat15na LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ltecat15na STATIC
        src/ltecat15na.c
        include/ltecat15na.h
)
add_library(Click.LTECat15NA  ALIAS lib_ltecat15na)



target_include_directories(lib_ltecat15na PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ltecat15na PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ltecat15na PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_ltecat15na PUBLIC MikroSDK.Conversions)

