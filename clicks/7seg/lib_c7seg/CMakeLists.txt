cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c7seg LANGUAGES MikroC)
else()
    project(lib_c7seg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c7seg STATIC
        src/c7seg.c
        include/c7seg.h
)
add_library(Click.7seg  ALIAS lib_c7seg)



target_include_directories(lib_c7seg PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c7seg PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c7seg PUBLIC MikroSDK.Driver)
