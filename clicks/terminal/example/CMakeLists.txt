cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_terminal LANGUAGES MikroC)
else()
    project(example_terminal LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_terminal
        main.c

)


############################ example_terminal GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_terminal PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_terminal PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_terminal PUBLIC MikroSDK.Log)
add_subdirectory(lib_terminal)
target_link_libraries(example_terminal PUBLIC Click.Terminal)
############################ example_terminal GENERATED CODE END ###########################
