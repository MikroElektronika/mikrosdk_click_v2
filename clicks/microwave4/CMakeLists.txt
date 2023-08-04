cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_microwave4 LANGUAGES MikroC)
else()
    project(example_microwave4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_microwave4
        example/main.c
    
)


############################ example_microwave4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_microwave4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_microwave4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_microwave4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_microwave4)
target_link_libraries(example_microwave4 PUBLIC Click.Microwave4)
############################ example_microwave4 GENERATED CODE END ###########################

