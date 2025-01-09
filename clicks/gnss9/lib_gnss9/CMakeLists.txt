cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnss9 LANGUAGES MikroC)
else()
    project(lib_gnss9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnss9 STATIC
        src/gnss9.c
        include/gnss9.h
)
add_library(Click.GNSS9  ALIAS lib_gnss9)



target_include_directories(lib_gnss9 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnss9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnss9 PUBLIC MikroSDK.Driver)

