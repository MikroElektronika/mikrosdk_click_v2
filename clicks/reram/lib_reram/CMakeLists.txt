cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_reram LANGUAGES MikroC)
else()
    project(lib_reram LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_reram STATIC
        src/reram.c
        include/reram.h
)
add_library(Click.Reram  ALIAS lib_reram)



target_include_directories(lib_reram PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_reram PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_reram PUBLIC MikroSDK.Driver)
