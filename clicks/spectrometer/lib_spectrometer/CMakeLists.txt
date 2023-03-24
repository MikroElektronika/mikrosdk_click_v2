cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_spectrometer LANGUAGES MikroC)
else()
    project(lib_spectrometer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_spectrometer STATIC
        src/spectrometer.c
        include/spectrometer.h
)
add_library(Click.Spectrometer  ALIAS lib_spectrometer)



target_include_directories(lib_spectrometer PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_spectrometer PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_spectrometer PUBLIC MikroSDK.Driver)
