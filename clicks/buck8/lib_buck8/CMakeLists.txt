cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck8 LANGUAGES MikroC)
else()
    project(lib_buck8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck8 STATIC
        src/buck8.c
        include/buck8.h
)
add_library(Click.Buck8  ALIAS lib_buck8)



target_include_directories(lib_buck8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck8 PUBLIC MikroSDK.Driver)
