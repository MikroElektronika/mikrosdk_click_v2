cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_current2 LANGUAGES MikroC)
else()
    project(lib_current2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_current2 STATIC
        src/current2.c
        include/current2.h
)
add_library(Click.Current2  ALIAS lib_current2)



target_include_directories(lib_current2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_current2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_current2 PUBLIC MikroSDK.Driver)
