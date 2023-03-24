cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_enocean3 LANGUAGES MikroC)
else()
    project(lib_enocean3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_enocean3 STATIC
        src/enocean3.c
        include/enocean3.h
)
add_library(Click.Enocean3  ALIAS lib_enocean3)



target_include_directories(lib_enocean3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_enocean3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_enocean3 PUBLIC MikroSDK.Driver)
