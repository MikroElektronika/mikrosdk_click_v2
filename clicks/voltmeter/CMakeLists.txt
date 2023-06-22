cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_voltmeter LANGUAGES MikroC)
else()
    project(example_voltmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_voltmeter
        example/main.c

)


############################ example_voltmeter GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_voltmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_voltmeter PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_voltmeter PUBLIC MikroSDK.Log)
add_subdirectory(lib_voltmeter)
target_link_libraries(example_voltmeter PUBLIC Click.Voltmeter)
############################ example_voltmeter GENERATED CODE END ###########################
