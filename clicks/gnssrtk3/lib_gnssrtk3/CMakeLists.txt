cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnssrtk3 LANGUAGES MikroC)
else()
    project(lib_gnssrtk3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnssrtk3 STATIC
        src/gnssrtk3.c
        include/gnssrtk3.h
)
add_library(Click.GNSSRTK3  ALIAS lib_gnssrtk3)



target_include_directories(lib_gnssrtk3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnssrtk3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnssrtk3 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnssrtk3 PUBLIC MikroSDK.GenericPointer)

