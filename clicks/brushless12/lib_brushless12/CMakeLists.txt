cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless12 LANGUAGES MikroC)
else()
    project(lib_brushless12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless12 STATIC
        src/brushless12.c
        include/brushless12.h
)
add_library(Click.Brushless12  ALIAS lib_brushless12)



target_include_directories(lib_brushless12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless12 PUBLIC MikroSDK.Driver)
