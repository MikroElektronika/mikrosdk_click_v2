cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pressure2330ba LANGUAGES MikroC)
else()
    project(example_pressure2330ba LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pressure2330ba
        example/main.c
    
)


############################ example_pressure2330ba GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pressure2330ba PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pressure2330ba PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pressure2330ba PUBLIC MikroSDK.Log)
add_subdirectory(lib_pressure2330ba)
target_link_libraries(example_pressure2330ba PUBLIC Click.Pressure2330BA)
############################ example_pressure2330ba GENERATED CODE END ###########################

