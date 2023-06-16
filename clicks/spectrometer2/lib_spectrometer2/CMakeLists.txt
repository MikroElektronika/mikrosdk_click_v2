cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_spectrometer2 LANGUAGES MikroC)
else()
    project(lib_spectrometer2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_spectrometer2 STATIC
        src/spectrometer2.c
        include/spectrometer2.h
)
add_library(Click.Spectrometer2  ALIAS lib_spectrometer2)



target_include_directories(lib_spectrometer2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_spectrometer2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_spectrometer2 PUBLIC MikroSDK.Driver)
