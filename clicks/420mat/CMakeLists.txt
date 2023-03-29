cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c420mat LANGUAGES MikroC)
else()
    project(example_c420mat LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c420mat
        example/main.c

)


############################ example_c420mat GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c420mat PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c420mat PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c420mat PUBLIC MikroSDK.Log)
add_subdirectory(lib_c420mat)
target_link_libraries(example_c420mat PUBLIC Click.420mat)
############################ example_c420mat GENERATED CODE END ###########################
