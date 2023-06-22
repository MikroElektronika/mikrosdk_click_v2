cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lr2 LANGUAGES MikroC)
else()
    project(example_lr2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lr2
        main.c
    
)

############################ example_lr2 GENERATED CODE START ###########################
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lr2 PUBLIC MikroSDK.Log)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_lr2 PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lr2 PUBLIC MikroSDK.Board)
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lr2 PUBLIC MikroC.Core)
add_subdirectory(lib_lr2)
target_link_libraries(example_lr2 PUBLIC Click.LR2)
############################ example_lr2 GENERATED CODE END ###########################


