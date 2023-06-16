cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pressure8 LANGUAGES MikroC)
else()
    project(example_pressure8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pressure8
        example/main.c

)


############################ example_pressure8 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pressure8 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pressure8 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pressure8 PUBLIC MikroSDK.Log)
add_subdirectory(lib_pressure8)
target_link_libraries(example_pressure8 PUBLIC Click.Pressure8)
############################ example_pressure8 GENERATED CODE END ###########################
