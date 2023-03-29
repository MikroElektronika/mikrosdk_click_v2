cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lem LANGUAGES MikroC)
else()
    project(example_lem LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lem
        example/main.c

)


############################ example_lem GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lem PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lem PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lem PUBLIC MikroSDK.Log)
add_subdirectory(lib_lem)
target_link_libraries(example_lem PUBLIC Click.Lem)
############################ example_lem GENERATED CODE END ###########################
