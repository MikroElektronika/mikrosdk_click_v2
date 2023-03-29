cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless22 LANGUAGES MikroC)
else()
    project(lib_brushless22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless22 STATIC
        src/brushless22.c
        include/brushless22.h
)
add_library(Click.Brushless22  ALIAS lib_brushless22)



target_include_directories(lib_brushless22 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless22 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless22 PUBLIC MikroSDK.Driver)
