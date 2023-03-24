cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_fan6 LANGUAGES MikroC)
else()
    project(lib_fan6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_fan6 STATIC
        src/fan6.c
        include/fan6.h
)
add_library(Click.Fan6  ALIAS lib_fan6)



target_include_directories(lib_fan6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_fan6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_fan6 PUBLIC MikroSDK.Driver)
