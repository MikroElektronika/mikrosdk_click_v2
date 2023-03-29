cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_enocean2 LANGUAGES MikroC)
else()
    project(lib_enocean2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_enocean2 STATIC
        src/enocean2.c
        include/enocean2.h
)
add_library(Click.EnOcean2  ALIAS lib_enocean2)



target_include_directories(lib_enocean2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_enocean2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_enocean2 PUBLIC MikroSDK.Driver)
