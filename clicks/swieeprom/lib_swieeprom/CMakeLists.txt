cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_swieeprom LANGUAGES MikroC)
else()
    project(lib_swieeprom LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_swieeprom STATIC
        src/swieeprom.c
        include/swieeprom.h
)
add_library(Click.SWIEEPROM  ALIAS lib_swieeprom)



target_include_directories(lib_swieeprom PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_swieeprom PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_swieeprom PUBLIC MikroSDK.Driver)

