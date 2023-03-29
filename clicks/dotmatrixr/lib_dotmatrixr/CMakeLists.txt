cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dotmatrixr LANGUAGES MikroC)
else()
    project(lib_dotmatrixr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dotmatrixr STATIC
        src/dotmatrixr.c
        include/dotmatrixr.h
)
add_library(Click.DotMatrixR  ALIAS lib_dotmatrixr)



target_include_directories(lib_dotmatrixr PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dotmatrixr PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dotmatrixr PUBLIC MikroSDK.Driver)
