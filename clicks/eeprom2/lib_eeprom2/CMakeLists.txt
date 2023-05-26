cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_eeprom2 LANGUAGES MikroC)
else()
    project(lib_eeprom2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_eeprom2 STATIC
        src/eeprom2.c
        include/eeprom2.h
)
add_library(Click.Eeprom2  ALIAS lib_eeprom2)



target_include_directories(lib_eeprom2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_eeprom2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_eeprom2 PUBLIC MikroSDK.Driver)
