cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_button4 LANGUAGES MikroC)
else()
    project(lib_button4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_button4 STATIC
        src/button4.c
        include/button4.h
)
add_library(Click.Button4  ALIAS lib_button4)



target_include_directories(lib_button4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_button4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_button4 PUBLIC MikroSDK.Driver)

