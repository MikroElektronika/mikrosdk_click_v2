cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnss LANGUAGES MikroC)
else()
    project(lib_gnss LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnss STATIC
        src/gnss.c
        include/gnss.h
)
add_library(Click.Gnss  ALIAS lib_gnss)



target_include_directories(lib_gnss PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnss PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnss PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnss PUBLIC MikroSDK.GenericPointer)
