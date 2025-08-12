cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eeprom17 LANGUAGES MikroC)
else()
    project(lib_eeprom17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eeprom17 STATIC
        src/eeprom17.c
        include/eeprom17.h
)
add_library(Click.EEPROM17  ALIAS lib_eeprom17)



target_include_directories(lib_eeprom17 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eeprom17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eeprom17 PUBLIC MikroSDK.Driver)

