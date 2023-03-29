cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ntag5link LANGUAGES MikroC)
else()
    project(lib_ntag5link LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ntag5link STATIC
        src/ntag5link.c
        include/ntag5link.h
)
add_library(Click.NTAG5Link  ALIAS lib_ntag5link)



target_include_directories(lib_ntag5link PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ntag5link PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ntag5link PUBLIC MikroSDK.Driver)
