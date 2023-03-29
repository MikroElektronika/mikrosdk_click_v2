cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_digivref LANGUAGES MikroC)
else()
    project(lib_digivref LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_digivref STATIC
        src/digivref.c
        include/digivref.h
)
add_library(Click.DigiVref  ALIAS lib_digivref)



target_include_directories(lib_digivref PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_digivref PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_digivref PUBLIC MikroSDK.Driver)
