cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_evc LANGUAGES MikroC)
else()
    project(lib_evc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_evc STATIC
        src/evc.c
        include/evc.h
)
add_library(Click.EVC  ALIAS lib_evc)



target_include_directories(lib_evc PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_evc PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_evc PUBLIC MikroSDK.Driver)
