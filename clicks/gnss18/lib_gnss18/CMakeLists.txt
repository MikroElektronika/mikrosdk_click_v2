cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnss18 LANGUAGES MikroC)
else()
    project(lib_gnss18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnss18 STATIC
        src/gnss18.c
        include/gnss18.h
)
add_library(Click.GNSS18  ALIAS lib_gnss18)



target_include_directories(lib_gnss18 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnss18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnss18 PUBLIC MikroSDK.Driver)

