cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnssrtk3da LANGUAGES MikroC)
else()
    project(lib_gnssrtk3da LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnssrtk3da STATIC
        src/gnssrtk3da.c
        include/gnssrtk3da.h
)
add_library(Click.GNSSRTK3DA  ALIAS lib_gnssrtk3da)



target_include_directories(lib_gnssrtk3da PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnssrtk3da PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnssrtk3da PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnssrtk3da PUBLIC MikroSDK.GenericPointer)

