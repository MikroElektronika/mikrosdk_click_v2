cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_battman LANGUAGES MikroC)
else()
    project(lib_battman LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_battman STATIC
        src/battman.c
        include/battman.h
)
add_library(Click.BattMan  ALIAS lib_battman)



target_include_directories(lib_battman PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_battman PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_battman PUBLIC MikroSDK.Driver)
