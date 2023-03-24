cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_spiisolator3 LANGUAGES MikroC)
else()
    project(lib_spiisolator3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_spiisolator3 STATIC
        src/spiisolator3.c
        include/spiisolator3.h
)
add_library(Click.SpiIsolator3  ALIAS lib_spiisolator3)



target_include_directories(lib_spiisolator3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_spiisolator3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_spiisolator3 PUBLIC MikroSDK.Driver)
