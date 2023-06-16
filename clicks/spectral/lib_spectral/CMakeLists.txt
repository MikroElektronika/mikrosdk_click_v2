cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_spectral LANGUAGES MikroC)
else()
    project(lib_spectral LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_spectral STATIC
        src/spectral.c
        include/spectral.h
)
add_library(Click.Spectral  ALIAS lib_spectral)



target_include_directories(lib_spectral PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_spectral PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_spectral PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_spectral PUBLIC MikroSDK.GenericPointer)
