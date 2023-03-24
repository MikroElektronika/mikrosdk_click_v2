cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irsense LANGUAGES MikroC)
else()
    project(lib_irsense LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irsense STATIC
        src/irsense.c
        include/irsense.h
)
add_library(Click.IrSense  ALIAS lib_irsense)



target_include_directories(lib_irsense PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irsense PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irsense PUBLIC MikroSDK.Driver)
