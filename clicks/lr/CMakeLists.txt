cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lr LANGUAGES MikroC)
else()
    project(example_lr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lr
        example/main.c
    
)

############################ example_lr GENERATED CODE START ###########################
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lr PUBLIC MikroSDK.Log)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_lr PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lr PUBLIC MikroSDK.Board)
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lr PUBLIC MikroC.Core)
add_subdirectory(lib_lr)
target_link_libraries(example_lr PUBLIC Click.LR)
############################ example_lr GENERATED CODE END ###########################


