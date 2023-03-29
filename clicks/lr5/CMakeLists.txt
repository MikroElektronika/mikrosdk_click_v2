cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lr5 LANGUAGES MikroC)
else()
    project(example_lr5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lr5
        example/main.c

)


############################ example_lr5 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lr5 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lr5 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lr5 PUBLIC MikroSDK.Log)
add_subdirectory(lib_lr5)
target_link_libraries(example_lr5 PUBLIC Click.LR5)
############################ example_lr5 GENERATED CODE END ###########################
