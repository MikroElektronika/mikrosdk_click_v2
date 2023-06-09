cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pll LANGUAGES MikroC)
else()
    project(example_pll LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pll
        example/main.c

)


############################ example_pll GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pll PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pll PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pll PUBLIC MikroSDK.Log)
add_subdirectory(lib_pll)
target_link_libraries(example_pll PUBLIC Click.Pll)
############################ example_pll GENERATED CODE END ###########################
