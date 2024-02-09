cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_cdc LANGUAGES MikroC)
else()
    project(example_cdc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_cdc
        main.c
    
)


############################ example_cdc GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_cdc PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_cdc PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_cdc PUBLIC MikroSDK.Log)
add_subdirectory(lib_cdc)
target_link_libraries(example_cdc PUBLIC Click.CDC)
############################ example_cdc GENERATED CODE END ###########################

