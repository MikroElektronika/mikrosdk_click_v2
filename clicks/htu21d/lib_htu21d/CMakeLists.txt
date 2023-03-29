cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_htu21d LANGUAGES MikroC)
else()
    project(lib_htu21d LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_htu21d STATIC
        src/htu21d.c
        include/htu21d.h
)
add_library(Click.Htu21d  ALIAS lib_htu21d)



target_include_directories(lib_htu21d PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_htu21d PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_htu21d PUBLIC MikroSDK.Driver)
