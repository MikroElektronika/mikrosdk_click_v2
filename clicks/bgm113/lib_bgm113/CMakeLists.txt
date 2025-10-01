cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bgm113 LANGUAGES MikroC)
else()
    project(lib_bgm113 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bgm113 STATIC
        src/bgm113.c
        include/bgm113.h
)
add_library(Click.BGM113  ALIAS lib_bgm113)



target_include_directories(lib_bgm113 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bgm113 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bgm113 PUBLIC MikroSDK.Driver)

