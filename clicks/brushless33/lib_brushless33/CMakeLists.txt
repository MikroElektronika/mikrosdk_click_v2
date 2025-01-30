cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless33 LANGUAGES MikroC)
else()
    project(lib_brushless33 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless33 STATIC
        src/brushless33.c
        include/brushless33.h
)
add_library(Click.Brushless33  ALIAS lib_brushless33)



target_include_directories(lib_brushless33 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless33 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless33 PUBLIC MikroSDK.Driver)

