cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hbridge15 LANGUAGES MikroC)
else()
    project(lib_hbridge15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hbridge15 STATIC
        src/hbridge15.c
        include/hbridge15.h
)
add_library(Click.HBridge15  ALIAS lib_hbridge15)



target_include_directories(lib_hbridge15 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hbridge15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hbridge15 PUBLIC MikroSDK.Driver)

