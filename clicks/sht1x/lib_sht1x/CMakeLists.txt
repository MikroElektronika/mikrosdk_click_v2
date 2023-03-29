cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_sht1x LANGUAGES MikroC)
else()
    project(lib_sht1x LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_sht1x STATIC
        src/sht1x.c
        include/sht1x.h
)
add_library(Click.Sht1x  ALIAS lib_sht1x)



target_include_directories(lib_sht1x PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_sht1x PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_sht1x PUBLIC MikroSDK.Driver)
