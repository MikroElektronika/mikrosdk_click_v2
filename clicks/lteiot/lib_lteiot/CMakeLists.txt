cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lteiot LANGUAGES MikroC)
else()
    project(lib_lteiot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lteiot STATIC
        src/lteiot.c
        include/lteiot.h
)
add_library(Click.LteIot  ALIAS lib_lteiot)



target_include_directories(lib_lteiot PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lteiot PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lteiot PUBLIC MikroSDK.Driver)
