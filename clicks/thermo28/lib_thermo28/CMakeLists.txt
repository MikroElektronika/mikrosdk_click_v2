cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo28 LANGUAGES MikroC)
else()
    project(lib_thermo28 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo28 STATIC
        src/thermo28.c
        include/thermo28.h
)
add_library(Click.Thermo28  ALIAS lib_thermo28)



target_include_directories(lib_thermo28 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo28 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo28 PUBLIC MikroSDK.Driver)
