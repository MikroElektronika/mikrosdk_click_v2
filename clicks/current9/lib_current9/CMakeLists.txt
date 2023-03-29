cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current9 LANGUAGES MikroC)
else()
    project(lib_current9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current9 STATIC
        src/current9.c
        include/current9.h
)
add_library(Click.Current9  ALIAS lib_current9)



target_include_directories(lib_current9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current9 PUBLIC MikroSDK.Driver)
