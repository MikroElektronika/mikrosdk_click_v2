cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_spectral2 LANGUAGES MikroC)
else()
    project(lib_spectral2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_spectral2 STATIC
        src/spectral2.c
        include/spectral2.h
)
add_library(Click.Spectral2  ALIAS lib_spectral2)



target_include_directories(lib_spectral2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_spectral2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_spectral2 PUBLIC MikroSDK.Driver)
