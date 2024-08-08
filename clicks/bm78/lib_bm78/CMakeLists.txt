cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bm78 LANGUAGES MikroC)
else()
    project(lib_bm78 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bm78
STATIC
src/bm78.c
include/bm78.h
include/bm78_config.h
src/bm78_config.c
)
add_library(Click.BM78  ALIAS lib_bm78)



target_include_directories(lib_bm78 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bm78 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bm78 PUBLIC MikroSDK.Driver)

