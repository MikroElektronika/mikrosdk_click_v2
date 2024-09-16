cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless31 LANGUAGES MikroC)
else()
    project(lib_brushless31 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless31 STATIC
        src/brushless31.c
        include/brushless31.h
)
add_library(Click.Brushless31  ALIAS lib_brushless31)



target_include_directories(lib_brushless31 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless31 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless31 PUBLIC MikroSDK.Driver)

