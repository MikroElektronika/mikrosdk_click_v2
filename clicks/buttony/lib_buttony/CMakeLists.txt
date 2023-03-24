cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buttony LANGUAGES MikroC)
else()
    project(lib_buttony LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buttony STATIC
        src/buttony.c
        include/buttony.h
)
add_library(Click.ButtonY  ALIAS lib_buttony)



target_include_directories(lib_buttony PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buttony PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buttony PUBLIC MikroSDK.Driver)
