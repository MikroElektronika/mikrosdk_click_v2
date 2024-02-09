cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ibutton LANGUAGES MikroC)
else()
    project(lib_ibutton LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ibutton STATIC
        src/ibutton.c
        include/ibutton.h
)
add_library(Click.iButton  ALIAS lib_ibutton)



target_include_directories(lib_ibutton PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ibutton PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ibutton PUBLIC MikroSDK.Driver)

