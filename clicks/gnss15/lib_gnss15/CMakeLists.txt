cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnss15 LANGUAGES MikroC)
else()
    project(lib_gnss15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnss15 STATIC
        src/gnss15.c
        include/gnss15.h
)
add_library(Click.GNSS15  ALIAS lib_gnss15)



target_include_directories(lib_gnss15 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnss15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnss15 PUBLIC MikroSDK.Driver)

