cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mcp2518fd LANGUAGES MikroC)
else()
    project(example_mcp2518fd LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mcp2518fd
        main.c

)


############################ example_mcp2518fd GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mcp2518fd PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mcp2518fd PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mcp2518fd PUBLIC MikroSDK.Log)
add_subdirectory(lib_mcp2518fd)
target_link_libraries(example_mcp2518fd PUBLIC Click.MCP2518FD)
############################ example_mcp2518fd GENERATED CODE END ###########################
