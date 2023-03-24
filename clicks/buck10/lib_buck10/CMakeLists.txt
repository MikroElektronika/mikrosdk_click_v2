cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck10 LANGUAGES MikroC)
else()
    project(lib_buck10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck10 STATIC
        src/buck10.c
        include/buck10.h
)
add_library(Click.Buck10  ALIAS lib_buck10)



target_include_directories(lib_buck10 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck10 PUBLIC MikroSDK.Driver)
