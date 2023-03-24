cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo2 LANGUAGES MikroC)
else()
    project(lib_thermo2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo2 STATIC
        src/thermo2.c
        include/thermo2.h
)
add_library(Click.Thermo2  ALIAS lib_thermo2)



target_include_directories(lib_thermo2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo2 PUBLIC MikroSDK.Driver)
