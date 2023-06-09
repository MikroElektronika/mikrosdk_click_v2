cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ismrx LANGUAGES MikroC)
else()
    project(lib_ismrx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ismrx STATIC
        src/ismrx.c
        include/ismrx.h
)
add_library(Click.ISMRX  ALIAS lib_ismrx)

target_include_directories(lib_ismrx PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ismrx PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ismrx PUBLIC MikroSDK.Driver)
