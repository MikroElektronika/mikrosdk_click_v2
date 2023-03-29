cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lteiot2 LANGUAGES MikroC)
else()
    project(lib_lteiot2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lteiot2 STATIC
        src/lteiot2.c
        include/lteiot2.h
)
add_library(Click.LteIot2  ALIAS lib_lteiot2)



target_include_directories(lib_lteiot2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lteiot2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lteiot2 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_lteiot2 PUBLIC MikroSDK.GenericPointer)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_lteiot2 PUBLIC MikroSDK.Conversions)
