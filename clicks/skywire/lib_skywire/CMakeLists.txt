cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_skywire LANGUAGES MikroC)
else()
    project(lib_skywire LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_skywire STATIC
        src/skywire.c
        include/skywire.h
)
add_library(Click.Skywire  ALIAS lib_skywire)



target_include_directories(lib_skywire PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_skywire PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_skywire PUBLIC MikroSDK.Driver)

