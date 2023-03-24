cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless14 LANGUAGES MikroC)
else()
    project(lib_brushless14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless14 STATIC
        src/brushless14.c
        include/brushless14.h
)
add_library(Click.Brushless14  ALIAS lib_brushless14)



target_include_directories(lib_brushless14 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless14 PUBLIC MikroSDK.Driver)
