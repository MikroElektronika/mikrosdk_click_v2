cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_thermostat LANGUAGES MikroC)
else()
    project(example_thermostat LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_thermostat
        example/main.c

)


############################ example_thermostat GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_thermostat PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_thermostat PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_thermostat PUBLIC MikroSDK.Log)
add_subdirectory(lib_thermostat)
target_link_libraries(example_thermostat PUBLIC Click.Thermostat)
############################ example_thermostat GENERATED CODE END ###########################
