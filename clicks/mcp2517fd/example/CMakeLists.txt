cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mcp2517fd LANGUAGES MikroC)
else()
    project(example_mcp2517fd LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mcp2517fd
        main.c

)


############################ example_mcp2517fd GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mcp2517fd PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mcp2517fd PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mcp2517fd PUBLIC MikroSDK.Log)
add_subdirectory(lib_mcp2517fd)
target_link_libraries(example_mcp2517fd PUBLIC Click.MCP2517FD)
############################ example_mcp2517fd GENERATED CODE END ###########################
