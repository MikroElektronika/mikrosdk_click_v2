cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_flash3 LANGUAGES MikroC)
else()
    project(lib_flash3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_flash3 STATIC
        src/flash3.c
        include/flash3.h
)
add_library(Click.Flash3  ALIAS lib_flash3)



target_include_directories(lib_flash3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_flash3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_flash3 PUBLIC MikroSDK.Driver)
