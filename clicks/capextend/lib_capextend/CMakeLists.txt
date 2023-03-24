cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_capextend LANGUAGES MikroC)
else()
    project(lib_capextend LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_capextend STATIC
        src/capextend.c
        include/capextend.h
)
add_library(Click.CapExtend  ALIAS lib_capextend)



target_include_directories(lib_capextend PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_capextend PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_capextend PUBLIC MikroSDK.Driver)
