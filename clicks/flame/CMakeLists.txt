cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_flame LANGUAGES MikroC)
else()
    project(example_flame LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_flame
        example/main.c

)


############################ example_flame GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_flame PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_flame PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_flame PUBLIC MikroSDK.Log)
add_subdirectory(lib_flame)
target_link_libraries(example_flame PUBLIC Click.Flame)
############################ example_flame GENERATED CODE END ###########################
