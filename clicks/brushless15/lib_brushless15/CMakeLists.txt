cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless15 LANGUAGES MikroC)
else()
    project(lib_brushless15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless15 STATIC
        src/brushless15.c
        include/brushless15.h
)
add_library(Click.Brushless15  ALIAS lib_brushless15)



target_include_directories(lib_brushless15 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless15 PUBLIC MikroSDK.Driver)
