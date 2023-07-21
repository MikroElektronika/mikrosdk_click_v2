cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wheatstone LANGUAGES MikroC)
else()
    project(lib_wheatstone LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wheatstone STATIC
        src/wheatstone.c
        include/wheatstone.h
)
add_library(Click.Wheatstone  ALIAS lib_wheatstone)



target_include_directories(lib_wheatstone PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wheatstone PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wheatstone PUBLIC MikroSDK.Driver)
