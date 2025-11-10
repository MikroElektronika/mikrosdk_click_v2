cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pushbutton LANGUAGES MikroC)
else()
    project(lib_pushbutton LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pushbutton STATIC
        src/pushbutton.c
        include/pushbutton.h
)
add_library(Click.PushButton  ALIAS lib_pushbutton)



target_include_directories(lib_pushbutton PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pushbutton PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pushbutton PUBLIC MikroSDK.Driver)

