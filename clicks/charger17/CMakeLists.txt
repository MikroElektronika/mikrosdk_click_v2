cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_charger17 LANGUAGES MikroC)
else()
    project(example_charger17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_charger17
        example/main.c

)


############################ example_charger17 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_charger17 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_charger17 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_charger17 PUBLIC MikroSDK.Log)
add_subdirectory(lib_charger17)
target_link_libraries(example_charger17 PUBLIC Click.Charger17)
############################ example_charger17 GENERATED CODE END ###########################
