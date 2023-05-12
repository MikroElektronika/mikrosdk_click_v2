cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_counter LANGUAGES MikroC)
else()
    project(example_counter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_counter
        example/main.c

)


############################ example_counter GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_counter PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_counter PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_counter PUBLIC MikroSDK.Log)
add_subdirectory(lib_counter)
target_link_libraries(example_counter PUBLIC Click.Counter)
############################ example_counter GENERATED CODE END ###########################
