cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irsense3 LANGUAGES MikroC)
else()
    project(lib_irsense3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irsense3 STATIC
        src/irsense3.c
        include/irsense3.h
)
add_library(Click.IrSense3  ALIAS lib_irsense3)



target_include_directories(lib_irsense3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irsense3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irsense3 PUBLIC MikroSDK.Driver)
