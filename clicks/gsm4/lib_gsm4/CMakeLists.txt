cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gsm4 LANGUAGES MikroC)
else()
    project(lib_gsm4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gsm4 STATIC
        src/gsm4.c
        include/gsm4.h
)
add_library(Click.GSM4  ALIAS lib_gsm4)



target_include_directories(lib_gsm4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gsm4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gsm4 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_gsm4 PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gsm4 PUBLIC MikroSDK.GenericPointer)
