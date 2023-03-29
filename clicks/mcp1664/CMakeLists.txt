cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mcp1664 LANGUAGES MikroC)
else()
    project(example_mcp1664 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mcp1664
        example/main.c

)


############################ example_mcp1664 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mcp1664 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mcp1664 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mcp1664 PUBLIC MikroSDK.Log)
add_subdirectory(lib_mcp1664)
target_link_libraries(example_mcp1664 PUBLIC Click.Mcp1664)
############################ example_mcp1664 GENERATED CODE END ###########################
