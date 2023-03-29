cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_boost LANGUAGES MikroC)
else()
    project(example_boost LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_boost
        example/main.c

)


############################ example_boost GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_boost PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_boost PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_boost PUBLIC MikroSDK.Log)
add_subdirectory(lib_boost)
target_link_libraries(example_boost PUBLIC Click.Boost)
############################ example_boost GENERATED CODE END ###########################
