cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gsm LANGUAGES MikroC)
else()
    project(lib_gsm LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gsm STATIC
        src/gsm.c
        include/gsm.h
)
add_library(Click.GSM  ALIAS lib_gsm)



target_include_directories(lib_gsm PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gsm PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gsm PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_gsm PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gsm PUBLIC MikroSDK.GenericPointer)
