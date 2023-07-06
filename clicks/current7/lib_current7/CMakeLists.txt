cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current7 LANGUAGES MikroC)
else()
    project(lib_current7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current7 STATIC
        src/current7.c
        include/current7.h
)
add_library(Click.Current7  ALIAS lib_current7)



target_include_directories(lib_current7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current7 PUBLIC MikroSDK.Driver)
