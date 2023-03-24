cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo22 LANGUAGES MikroC)
else()
    project(lib_thermo22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo22 STATIC
        src/thermo22.c
        include/thermo22.h
)
add_library(Click.Thermo22  ALIAS lib_thermo22)



target_include_directories(lib_thermo22 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo22 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo22 PUBLIC MikroSDK.Driver)
