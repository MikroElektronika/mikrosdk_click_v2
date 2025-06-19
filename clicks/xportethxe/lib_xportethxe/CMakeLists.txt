cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_xportethxe LANGUAGES MikroC)
else()
    project(lib_xportethxe LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_xportethxe STATIC
        src/xportethxe.c
        include/xportethxe.h
)
add_library(Click.XPortETHXE  ALIAS lib_xportethxe)



target_include_directories(lib_xportethxe PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_xportethxe PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_xportethxe PUBLIC MikroSDK.Driver)

