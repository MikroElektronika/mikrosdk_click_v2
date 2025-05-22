cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnssrtk4 LANGUAGES MikroC)
else()
    project(lib_gnssrtk4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnssrtk4 STATIC
        src/gnssrtk4.c
        include/gnssrtk4.h
)
add_library(Click.GNSSRTK4  ALIAS lib_gnssrtk4)



target_include_directories(lib_gnssrtk4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnssrtk4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnssrtk4 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnssrtk4 PUBLIC MikroSDK.GenericPointer)

