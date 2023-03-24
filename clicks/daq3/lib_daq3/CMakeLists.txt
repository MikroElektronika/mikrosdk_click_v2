cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_daq3 LANGUAGES MikroC)
else()
    project(lib_daq3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_daq3 STATIC
        src/daq3.c
        include/daq3.h
)
add_library(Click.Daq3  ALIAS lib_daq3)



target_include_directories(lib_daq3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_daq3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_daq3 PUBLIC MikroSDK.Driver)
