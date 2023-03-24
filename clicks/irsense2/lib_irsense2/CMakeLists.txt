cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irsense2 LANGUAGES MikroC)
else()
    project(lib_irsense2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irsense2 STATIC
        src/irsense2.c
        include/irsense2.h
)
add_library(Click.IrSense2  ALIAS lib_irsense2)



target_include_directories(lib_irsense2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irsense2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irsense2 PUBLIC MikroSDK.Driver)
