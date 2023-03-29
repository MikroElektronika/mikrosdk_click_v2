cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_flash6 LANGUAGES MikroC)
else()
    project(lib_flash6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_flash6 STATIC
        src/flash6.c
        include/flash6.h
)
add_library(Click.Flash6  ALIAS lib_flash6)



target_include_directories(lib_flash6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_flash6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_flash6 PUBLIC MikroSDK.Driver)
