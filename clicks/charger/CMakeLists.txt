cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_charger LANGUAGES MikroC)
else()
    project(example_charger LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_charger
        example/main.c
    
)


############################ example_charger GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_charger PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_charger PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_charger PUBLIC MikroSDK.Log)
add_subdirectory(lib_charger)
target_link_libraries(example_charger PUBLIC Click.Charger)
############################ example_charger GENERATED CODE END ###########################

