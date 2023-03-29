cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_stretch LANGUAGES MikroC)
else()
    project(lib_stretch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_stretch STATIC
        src/stretch.c
        include/stretch.h
)
add_library(Click.Stretch  ALIAS lib_stretch)



target_include_directories(lib_stretch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_stretch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_stretch PUBLIC MikroSDK.Driver)
