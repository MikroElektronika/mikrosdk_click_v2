cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lsm6dsl LANGUAGES MikroC)
else()
    project(example_lsm6dsl LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lsm6dsl
        example/main.c

)


############################ example_lsm6dsl GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lsm6dsl PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lsm6dsl PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lsm6dsl PUBLIC MikroSDK.Log)
add_subdirectory(lib_lsm6dsl)
target_link_libraries(example_lsm6dsl PUBLIC Click.Lsm6Dsl)
############################ example_lsm6dsl GENERATED CODE END ###########################
