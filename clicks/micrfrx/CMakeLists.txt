cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_micrfrx LANGUAGES MikroC)
else()
    project(example_micrfrx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_micrfrx
        example/main.c
    
)


############################ example_micrfrx GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_micrfrx PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_micrfrx PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_micrfrx PUBLIC MikroSDK.Log)
add_subdirectory(lib_micrfrx)
target_link_libraries(example_micrfrx PUBLIC Click.MICRFRX)
############################ example_micrfrx GENERATED CODE END ###########################

