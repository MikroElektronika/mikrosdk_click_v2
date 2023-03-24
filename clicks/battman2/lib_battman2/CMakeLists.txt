cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_battman2 LANGUAGES MikroC)
else()
    project(lib_battman2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_battman2 STATIC
        src/battman2.c
        include/battman2.h
)
add_library(Click.BATTMAN2  ALIAS lib_battman2)



target_include_directories(lib_battman2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_battman2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_battman2 PUBLIC MikroSDK.Driver)
