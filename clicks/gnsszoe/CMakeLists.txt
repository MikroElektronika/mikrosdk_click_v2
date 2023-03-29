cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gnsszoe LANGUAGES MikroC)
else()
    project(example_gnsszoe LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gnsszoe
        example/main.c

)


############################ example_gnsszoe GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gnsszoe PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gnsszoe PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gnsszoe PUBLIC MikroSDK.Log)
add_subdirectory(lib_gnsszoe)
target_link_libraries(example_gnsszoe PUBLIC Click.Gnsszoe)
############################ example_gnsszoe GENERATED CODE END ###########################
