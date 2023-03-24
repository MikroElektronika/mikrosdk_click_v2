cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lteiot3 LANGUAGES MikroC)
else()
    project(lib_lteiot3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lteiot3 STATIC
        src/lteiot3.c
        include/lteiot3.h
)
add_library(Click.LTEIoT3  ALIAS lib_lteiot3)



target_include_directories(lib_lteiot3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lteiot3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lteiot3 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_lteiot3 PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_lteiot3 PUBLIC MikroSDK.GenericPointer)
