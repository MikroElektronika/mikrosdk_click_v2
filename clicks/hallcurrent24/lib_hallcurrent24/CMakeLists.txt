cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent24 LANGUAGES MikroC)
else()
    project(lib_hallcurrent24 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent24 STATIC
        src/hallcurrent24.c
        include/hallcurrent24.h
)
add_library(Click.HallCurrent24  ALIAS lib_hallcurrent24)



target_include_directories(lib_hallcurrent24 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent24 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent24 PUBLIC MikroSDK.Driver)

