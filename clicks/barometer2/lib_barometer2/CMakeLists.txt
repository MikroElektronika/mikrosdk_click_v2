cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_barometer2 LANGUAGES MikroC)
else()
    project(lib_barometer2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_barometer2 STATIC
        src/barometer2.c
        include/barometer2.h
)
add_library(Click.Barometer2  ALIAS lib_barometer2)



target_include_directories(lib_barometer2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_barometer2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_barometer2 PUBLIC MikroSDK.Driver)
