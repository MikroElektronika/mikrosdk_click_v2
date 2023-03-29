cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless16 LANGUAGES MikroC)
else()
    project(lib_brushless16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless16 STATIC
        src/brushless16.c
        include/brushless16.h
)
add_library(Click.Brushless16  ALIAS lib_brushless16)



target_include_directories(lib_brushless16 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless16 PUBLIC MikroSDK.Driver)
