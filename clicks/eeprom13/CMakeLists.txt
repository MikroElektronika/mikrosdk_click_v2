cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_eeprom13 LANGUAGES MikroC)
else()
    project(example_eeprom13 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_eeprom13
        example/main.c
    
)


############################ example_eeprom13 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_eeprom13 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_eeprom13 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_eeprom13 PUBLIC MikroSDK.Log)
add_subdirectory(lib_eeprom13)
target_link_libraries(example_eeprom13 PUBLIC Click.EEPROM13)
############################ example_eeprom13 GENERATED CODE END ###########################

