cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rn4678 LANGUAGES MikroC)
else()
    project(lib_rn4678 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rn4678 STATIC
        src/rn4678.c
        include/rn4678.h
)
add_library(Click.Rn4678  ALIAS lib_rn4678)



target_include_directories(lib_rn4678 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rn4678 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rn4678 PUBLIC MikroSDK.Driver)
