cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_canisolator LANGUAGES MikroC)
else()
    project(example_canisolator LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_canisolator
        example/main.c

)


############################ example_canisolator GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_canisolator PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_canisolator PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_canisolator PUBLIC MikroSDK.Log)
add_subdirectory(lib_canisolator)
target_link_libraries(example_canisolator PUBLIC Click.CanIsolator)
############################ example_canisolator GENERATED CODE END ###########################
