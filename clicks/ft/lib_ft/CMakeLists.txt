cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ft LANGUAGES MikroC)
else()
    project(lib_ft LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ft STATIC
        src/ft.c
        include/ft.h
)
add_library(Click.Ft  ALIAS lib_ft)



target_include_directories(lib_ft PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ft PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ft PUBLIC MikroSDK.Driver)
