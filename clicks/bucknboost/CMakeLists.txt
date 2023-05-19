cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_bucknboost LANGUAGES MikroC)
else()
    project(example_bucknboost LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_bucknboost
        example/main.c

)


############################ example_bucknboost GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_bucknboost PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_bucknboost PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_bucknboost PUBLIC MikroSDK.Log)
add_subdirectory(lib_bucknboost)
target_link_libraries(example_bucknboost PUBLIC Click.BucknBoost)
############################ example_bucknboost GENERATED CODE END ###########################
