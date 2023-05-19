cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current3 LANGUAGES MikroC)
else()
    project(lib_current3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current3 STATIC
        src/current3.c
        include/current3.h
)
add_library(Click.Current3  ALIAS lib_current3)



target_include_directories(lib_current3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current3 PUBLIC MikroSDK.Driver)
