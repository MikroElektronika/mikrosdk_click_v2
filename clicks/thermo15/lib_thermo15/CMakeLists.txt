cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo15 LANGUAGES MikroC)
else()
    project(lib_thermo15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo15 STATIC
        src/thermo15.c
        include/thermo15.h
)
add_library(Click.Thermo15  ALIAS lib_thermo15)



target_include_directories(lib_thermo15 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo15 PUBLIC MikroSDK.Driver)
