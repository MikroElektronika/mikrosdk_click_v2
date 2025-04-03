cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ltecat18 LANGUAGES MikroC)
else()
    project(lib_ltecat18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ltecat18 STATIC
        src/ltecat18.c
        include/ltecat18.h
)
add_library(Click.LTECat18  ALIAS lib_ltecat18)



target_include_directories(lib_ltecat18 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ltecat18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ltecat18 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_ltecat18 PUBLIC MikroSDK.Conversions)

