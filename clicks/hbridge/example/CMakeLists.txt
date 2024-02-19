cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hbridge LANGUAGES MikroC)
else()
    project(example_hbridge LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hbridge
        main.c
    
)


############################ example_hbridge GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hbridge PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hbridge PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hbridge PUBLIC MikroSDK.Log)
add_subdirectory(lib_hbridge)
target_link_libraries(example_hbridge PUBLIC Click.HBridge)
############################ example_hbridge GENERATED CODE END ###########################

