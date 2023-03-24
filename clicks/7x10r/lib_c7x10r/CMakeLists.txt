cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c7x10r LANGUAGES MikroC)
else()
    project(lib_c7x10r LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c7x10r STATIC
        src/c7x10r.c
        include/c7x10r.h    include/c7x10r_font.h
)
add_library(Click.7x10R  ALIAS lib_c7x10r)



target_include_directories(lib_c7x10r PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c7x10r PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c7x10r PUBLIC MikroSDK.Driver)
