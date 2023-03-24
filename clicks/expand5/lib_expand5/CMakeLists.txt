cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand5 LANGUAGES MikroC)
else()
    project(lib_expand5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand5 STATIC
        src/expand5.c
        include/expand5.h
)
add_library(Click.Expand5  ALIAS lib_expand5)



target_include_directories(lib_expand5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand5 PUBLIC MikroSDK.Driver)
