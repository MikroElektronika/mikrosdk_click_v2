cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irsense6 LANGUAGES MikroC)
else()
    project(lib_irsense6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irsense6 STATIC
        src/irsense6.c
        include/irsense6.h
)
add_library(Click.IRSense6  ALIAS lib_irsense6)



target_include_directories(lib_irsense6 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irsense6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irsense6 PUBLIC MikroSDK.Driver)

