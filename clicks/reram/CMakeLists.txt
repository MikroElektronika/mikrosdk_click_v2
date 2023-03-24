cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_reram LANGUAGES MikroC)
else()
    project(example_reram LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_reram
        example/main.c

)


############################ example_reram GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_reram PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_reram PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_reram PUBLIC MikroSDK.Log)
add_subdirectory(lib_reram)
target_link_libraries(example_reram PUBLIC Click.Reram)
############################ example_reram GENERATED CODE END ###########################
