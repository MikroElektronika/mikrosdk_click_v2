cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_swieeprom LANGUAGES MikroC)
else()
    project(example_swieeprom LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_swieeprom
        example/main.c
    
)


############################ example_swieeprom GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_swieeprom PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_swieeprom PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_swieeprom PUBLIC MikroSDK.Log)
add_subdirectory(lib_swieeprom)
target_link_libraries(example_swieeprom PUBLIC Click.SWIEEPROM)
############################ example_swieeprom GENERATED CODE END ###########################

