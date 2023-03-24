cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mbusrf4 LANGUAGES MikroC)
else()
    project(lib_mbusrf4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mbusrf4 STATIC
        src/mbusrf4.c
        include/mbusrf4.h
)
add_library(Click.MBusRf4  ALIAS lib_mbusrf4)



target_include_directories(lib_mbusrf4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mbusrf4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mbusrf4 PUBLIC MikroSDK.Driver)
