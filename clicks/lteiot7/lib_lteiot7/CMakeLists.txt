cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lteiot7 LANGUAGES MikroC)
else()
    project(lib_lteiot7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lteiot7 STATIC
        src/lteiot7.c
        include/lteiot7.h
)
add_library(Click.LTEIoT7  ALIAS lib_lteiot7)



target_include_directories(lib_lteiot7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lteiot7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lteiot7 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_lteiot7 PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_lteiot7 PUBLIC MikroSDK.GenericPointer)
