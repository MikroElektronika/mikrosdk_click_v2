cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mcp16331inv LANGUAGES MikroC)
else()
    project(example_mcp16331inv LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mcp16331inv
        main.c

)


############################ example_mcp16331inv GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mcp16331inv PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mcp16331inv PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mcp16331inv PUBLIC MikroSDK.Log)
add_subdirectory(lib_mcp16331inv)
target_link_libraries(example_mcp16331inv PUBLIC Click.Mcp16331Inv)
############################ example_mcp16331inv GENERATED CODE END ###########################
