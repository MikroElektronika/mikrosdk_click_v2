cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnss5 LANGUAGES MikroC)
else()
    project(lib_gnss5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnss5 STATIC
        src/gnss5.c
        include/gnss5.h
)
add_library(Click.Gnss5  ALIAS lib_gnss5)



target_include_directories(lib_gnss5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnss5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnss5 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnss5 PUBLIC MikroSDK.GenericPointer)
