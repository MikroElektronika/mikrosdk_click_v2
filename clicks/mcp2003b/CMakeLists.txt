cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mcp2003b LANGUAGES MikroC)
else()
    project(example_mcp2003b LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mcp2003b
        example/main.c
    
)


############################ example_mcp2003b GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mcp2003b PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mcp2003b PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mcp2003b PUBLIC MikroSDK.Log)
add_subdirectory(lib_mcp2003b)
target_link_libraries(example_mcp2003b PUBLIC Click.MCP2003B)
############################ example_mcp2003b GENERATED CODE END ###########################

