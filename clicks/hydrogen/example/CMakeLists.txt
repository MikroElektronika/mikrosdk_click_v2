cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hydrogen LANGUAGES MikroC)
else()
    project(example_hydrogen LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hydrogen
        main.c

)


############################ example_hydrogen GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hydrogen PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hydrogen PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hydrogen PUBLIC MikroSDK.Log)
add_subdirectory(lib_hydrogen)
target_link_libraries(example_hydrogen PUBLIC Click.Hydrogen)
############################ example_hydrogen GENERATED CODE END ###########################
