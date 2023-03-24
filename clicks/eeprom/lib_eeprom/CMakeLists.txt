cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eeprom LANGUAGES MikroC)
else()
    project(lib_eeprom LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eeprom STATIC
        src/eeprom.c
        include/eeprom.h
)
add_library(Click.Eeprom  ALIAS lib_eeprom)



target_include_directories(lib_eeprom PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eeprom PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eeprom PUBLIC MikroSDK.Driver)
