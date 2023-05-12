cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mcp2542 LANGUAGES MikroC)
else()
    project(example_mcp2542 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mcp2542
        example/main.c

)


############################ example_mcp2542 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mcp2542 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mcp2542 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mcp2542 PUBLIC MikroSDK.Log)
add_subdirectory(lib_mcp2542)
target_link_libraries(example_mcp2542 PUBLIC Click.Mcp2542)
############################ example_mcp2542 GENERATED CODE END ###########################
