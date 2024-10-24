cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnssmax2 LANGUAGES MikroC)
else()
    project(lib_gnssmax2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnssmax2 STATIC
        src/gnssmax2.c
        include/gnssmax2.h
)
add_library(Click.GNSSMAX2  ALIAS lib_gnssmax2)



target_include_directories(lib_gnssmax2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnssmax2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnssmax2 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnssmax2 PUBLIC MikroSDK.GenericPointer)

