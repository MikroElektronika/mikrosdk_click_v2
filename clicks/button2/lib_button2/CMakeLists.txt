cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_button2 LANGUAGES MikroC)
else()
    project(lib_button2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_button2 STATIC
        src/button2.c
        include/button2.h
)
add_library(Click.Button2  ALIAS lib_button2)



target_include_directories(lib_button2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_button2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_button2 PUBLIC MikroSDK.Driver)

