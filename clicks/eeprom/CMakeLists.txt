cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_eeprom LANGUAGES MikroC)
else()
    project(example_eeprom LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_eeprom
        example/main.c

)


############################ example_eeprom GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_eeprom PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_eeprom PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_eeprom PUBLIC MikroSDK.Log)
add_subdirectory(lib_eeprom)
target_link_libraries(example_eeprom PUBLIC Click.Eeprom)
############################ example_eeprom GENERATED CODE END ###########################
