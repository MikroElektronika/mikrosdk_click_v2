cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless24 LANGUAGES MikroC)
else()
    project(lib_brushless24 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless24 STATIC
        src/brushless24.c
        include/brushless24.h
)
add_library(Click.Brushless24  ALIAS lib_brushless24)



target_include_directories(lib_brushless24 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless24 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless24 PUBLIC MikroSDK.Driver)
