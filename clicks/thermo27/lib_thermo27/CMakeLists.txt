cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo27 LANGUAGES MikroC)
else()
    project(lib_thermo27 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo27 STATIC
        src/thermo27.c
        include/thermo27.h
)
add_library(Click.Thermo27  ALIAS lib_thermo27)



target_include_directories(lib_thermo27 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo27 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo27 PUBLIC MikroSDK.Driver)
