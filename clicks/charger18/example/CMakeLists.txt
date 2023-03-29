cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_charger18 LANGUAGES MikroC)
else()
    project(example_charger18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_charger18
        main.c

)


############################ example_charger18 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_charger18 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_charger18 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_charger18 PUBLIC MikroSDK.Log)
add_subdirectory(lib_charger18)
target_link_libraries(example_charger18 PUBLIC Click.Charger18)
############################ example_charger18 GENERATED CODE END ###########################
