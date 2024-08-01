cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ltecat13nax LANGUAGES MikroC)
else()
    project(lib_ltecat13nax LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ltecat13nax STATIC
        src/ltecat13nax.c
        include/ltecat13nax.h
)
add_library(Click.LTECat13NAX  ALIAS lib_ltecat13nax)



target_include_directories(lib_ltecat13nax PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ltecat13nax PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ltecat13nax PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_ltecat13nax PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_ltecat13nax PUBLIC MikroSDK.GenericPointer)
