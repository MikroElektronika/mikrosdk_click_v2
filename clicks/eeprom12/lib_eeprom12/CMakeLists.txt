cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eeprom12 LANGUAGES MikroC)
else()
    project(lib_eeprom12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eeprom12 STATIC
        src/eeprom12.c
        include/eeprom12.h
)
add_library(Click.EEPROM12  ALIAS lib_eeprom12)



target_include_directories(lib_eeprom12 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eeprom12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eeprom12 PUBLIC MikroSDK.Driver)

