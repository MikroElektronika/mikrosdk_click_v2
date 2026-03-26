cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo31 LANGUAGES MikroC)
else()
    project(lib_thermo31 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo31 STATIC
        src/thermo31.c
        include/thermo31.h
)
add_library(Click.Thermo31  ALIAS lib_thermo31)



target_include_directories(lib_thermo31 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo31 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo31 PUBLIC MikroSDK.Driver)

