cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless11 LANGUAGES MikroC)
else()
    project(lib_brushless11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless11 STATIC
        src/brushless11.c
        include/brushless11.h
)
add_library(Click.Brushless11  ALIAS lib_brushless11)



target_include_directories(lib_brushless11 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless11 PUBLIC MikroSDK.Driver)

