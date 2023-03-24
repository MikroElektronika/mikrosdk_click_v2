cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_heater LANGUAGES MikroC)
else()
    project(example_heater LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_heater
        example/main.c

)


############################ example_heater GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_heater PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_heater PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_heater PUBLIC MikroSDK.Log)
add_subdirectory(lib_heater)
target_link_libraries(example_heater PUBLIC Click.Heater)
############################ example_heater GENERATED CODE END ###########################
