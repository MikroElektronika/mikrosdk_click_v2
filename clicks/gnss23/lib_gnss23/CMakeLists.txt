cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnss23 LANGUAGES MikroC)
else()
    project(lib_gnss23 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnss23 STATIC
        src/gnss23.c
        include/gnss23.h
)
add_library(Click.GNSS23  ALIAS lib_gnss23)



target_include_directories(lib_gnss23 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnss23 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnss23 PUBLIC MikroSDK.Driver)

