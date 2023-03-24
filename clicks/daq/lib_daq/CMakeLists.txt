cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_daq LANGUAGES MikroC)
else()
    project(lib_daq LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_daq STATIC
        src/daq.c
        include/daq.h
)
add_library(Click.DAQ  ALIAS lib_daq)



target_include_directories(lib_daq PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_daq PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_daq PUBLIC MikroSDK.Driver)
