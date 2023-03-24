cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_eeprom6 LANGUAGES MikroC)
else()
    project(example_eeprom6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_eeprom6
        main.c

)


############################ example_eeprom6 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_eeprom6 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_eeprom6 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_eeprom6 PUBLIC MikroSDK.Log)
add_subdirectory(lib_eeprom6)
target_link_libraries(example_eeprom6 PUBLIC Click.EEPROM6)
############################ example_eeprom6 GENERATED CODE END ###########################
