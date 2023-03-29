cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_brushless23 LANGUAGES MikroC)
else()
    project(lib_brushless23 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_brushless23 STATIC
        src/brushless23.c
        include/brushless23.h
)
add_library(Click.Brushless23  ALIAS lib_brushless23)



target_include_directories(lib_brushless23 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_brushless23 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_brushless23 PUBLIC MikroSDK.Driver)
