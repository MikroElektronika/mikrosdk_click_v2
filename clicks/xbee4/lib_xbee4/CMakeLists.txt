cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_xbee4 LANGUAGES MikroC)
else()
    project(lib_xbee4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_xbee4 STATIC
        src/xbee4.c
        include/xbee4.h
)
add_library(Click.XBEE4  ALIAS lib_xbee4)



target_include_directories(lib_xbee4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_xbee4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_xbee4 PUBLIC MikroSDK.Driver)

