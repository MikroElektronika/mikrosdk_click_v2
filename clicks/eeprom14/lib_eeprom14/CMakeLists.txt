cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eeprom14 LANGUAGES MikroC)
else()
    project(lib_eeprom14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eeprom14 STATIC
        src/eeprom14.c
        include/eeprom14.h
)
add_library(Click.EEPROM14  ALIAS lib_eeprom14)



target_include_directories(lib_eeprom14 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eeprom14 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eeprom14 PUBLIC MikroSDK.Driver)

