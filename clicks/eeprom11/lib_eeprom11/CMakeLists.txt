cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eeprom11 LANGUAGES MikroC)
else()
    project(lib_eeprom11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eeprom11 STATIC
        src/eeprom11.c
        include/eeprom11.h
)
add_library(Click.EEPROM11  ALIAS lib_eeprom11)



target_include_directories(lib_eeprom11 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eeprom11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eeprom11 PUBLIC MikroSDK.Driver)

