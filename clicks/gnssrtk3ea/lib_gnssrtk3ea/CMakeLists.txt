cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnssrtk3ea LANGUAGES MikroC)
else()
    project(lib_gnssrtk3ea LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnssrtk3ea STATIC
        src/gnssrtk3ea.c
        include/gnssrtk3ea.h
)
add_library(Click.GNSSRTK3EA  ALIAS lib_gnssrtk3ea)



target_include_directories(lib_gnssrtk3ea PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnssrtk3ea PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnssrtk3ea PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnssrtk3ea PUBLIC MikroSDK.GenericPointer)

