cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pressure22 LANGUAGES MikroC)
else()
    project(example_pressure22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pressure22
        example/main.c
    
)


############################ example_pressure22 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pressure22 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pressure22 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pressure22 PUBLIC MikroSDK.Log)
add_subdirectory(lib_pressure22)
target_link_libraries(example_pressure22 PUBLIC Click.Pressure22)
############################ example_pressure22 GENERATED CODE END ###########################

