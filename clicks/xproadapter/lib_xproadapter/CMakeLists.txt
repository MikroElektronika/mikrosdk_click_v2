cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_xproadapter LANGUAGES MikroC)
else()
    project(lib_xproadapter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_xproadapter STATIC
        src/xproadapter.c
        include/xproadapter.h
)
add_library(Click.XPROAdapter  ALIAS lib_xproadapter)



target_include_directories(lib_xproadapter PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_xproadapter PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_xproadapter PUBLIC MikroSDK.Driver)

