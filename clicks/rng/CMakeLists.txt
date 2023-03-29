cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rng LANGUAGES MikroC)
else()
    project(example_rng LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rng
        example/main.c

)


############################ example_rng GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rng PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rng PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rng PUBLIC MikroSDK.Log)
add_subdirectory(lib_rng)
target_link_libraries(example_rng PUBLIC Click.Rng)
############################ example_rng GENERATED CODE END ###########################
