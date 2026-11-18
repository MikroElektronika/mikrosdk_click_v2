cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_chargepump LANGUAGES MikroC)
else()
    project(lib_chargepump LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_chargepump STATIC
        src/chargepump.c
        include/chargepump.h
)
add_library(Click.ChargePump  ALIAS lib_chargepump)



target_include_directories(lib_chargepump PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_chargepump PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_chargepump PUBLIC MikroSDK.Driver)

