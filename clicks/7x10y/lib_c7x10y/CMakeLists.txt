cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c7x10y LANGUAGES MikroC)
else()
    project(lib_c7x10y LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c7x10y STATIC
        src/c7x10y.c
        include/c7x10y.h    include/c7x10y_font.h
)
add_library(Click.7x10Y  ALIAS lib_c7x10y)



target_include_directories(lib_c7x10y PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c7x10y PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c7x10y PUBLIC MikroSDK.Driver)
