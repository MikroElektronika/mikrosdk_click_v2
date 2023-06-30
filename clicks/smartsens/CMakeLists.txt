cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_smartsens LANGUAGES MikroC)
else()
    project(example_smartsens LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_smartsens
        example/main.c

)


############################ example_smartsens GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_smartsens PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_smartsens PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_smartsens PUBLIC MikroSDK.Log)
add_subdirectory(lib_smartsens)
target_link_libraries(example_smartsens PUBLIC Click.SmartSens)
############################ example_smartsens GENERATED CODE END ###########################
