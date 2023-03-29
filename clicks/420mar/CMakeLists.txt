cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c420mar LANGUAGES MikroC)
else()
    project(example_c420mar LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c420mar
        example/main.c

)


############################ example_c420mar GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c420mar PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c420mar PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c420mar PUBLIC MikroSDK.Log)
add_subdirectory(lib_c420mar)
target_link_libraries(example_c420mar PUBLIC Click.420MaR)
############################ example_c420mar GENERATED CODE END ###########################
