cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mram4 LANGUAGES MikroC)
else()
    project(example_mram4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mram4
        example/main.c
    
)


############################ example_mram4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mram4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mram4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mram4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_mram4)
target_link_libraries(example_mram4 PUBLIC Click.MRAM4)
############################ example_mram4 GENERATED CODE END ###########################

