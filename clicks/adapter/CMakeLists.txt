cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_adapter LANGUAGES MikroC)
else()
    project(example_adapter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_adapter
        example/main.c

)


############################ example_adapter GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_adapter PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_adapter PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_adapter PUBLIC MikroSDK.Log)
add_subdirectory(lib_adapter)
target_link_libraries(example_adapter PUBLIC Click.Adapter)
############################ example_adapter GENERATED CODE END ###########################
