cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo30 LANGUAGES MikroC)
else()
    project(lib_thermo30 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo30 STATIC
        src/thermo30.c
        include/thermo30.h
)
add_library(Click.Thermo30  ALIAS lib_thermo30)



target_include_directories(lib_thermo30 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo30 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo30 PUBLIC MikroSDK.Driver)

