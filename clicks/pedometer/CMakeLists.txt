cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pedometer LANGUAGES MikroC)
else()
    project(example_pedometer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pedometer
        example/main.c

)


############################ example_pedometer GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pedometer PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pedometer PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pedometer PUBLIC MikroSDK.Log)
add_subdirectory(lib_pedometer)
target_link_libraries(example_pedometer PUBLIC Click.Pedometer)
############################ example_pedometer GENERATED CODE END ###########################
