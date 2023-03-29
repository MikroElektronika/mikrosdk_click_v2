cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lteiot9 LANGUAGES MikroC)
else()
    project(lib_lteiot9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lteiot9 STATIC
        src/lteiot9.c
        include/lteiot9.h
)
add_library(Click.LTEIoT9  ALIAS lib_lteiot9)



target_include_directories(lib_lteiot9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lteiot9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lteiot9 PUBLIC MikroSDK.Driver)
