cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnss25 LANGUAGES MikroC)
else()
    project(lib_gnss25 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnss25 STATIC
        src/gnss25.c
        include/gnss25.h
)
add_library(Click.GNSS25  ALIAS lib_gnss25)



target_include_directories(lib_gnss25 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnss25 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnss25 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnss25 PUBLIC MikroSDK.GenericPointer)

