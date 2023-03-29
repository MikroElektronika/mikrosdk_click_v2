cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_fan4 LANGUAGES MikroC)
else()
    project(lib_fan4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_fan4 STATIC
        src/fan4.c
        include/fan4.h
)
add_library(Click.Fan4  ALIAS lib_fan4)



target_include_directories(lib_fan4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_fan4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_fan4 PUBLIC MikroSDK.Driver)
