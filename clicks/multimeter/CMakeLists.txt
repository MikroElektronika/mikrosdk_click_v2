cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_multimeter LANGUAGES MikroC)
else()
    project(example_multimeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_multimeter
        example/main.c

)


############################ example_multimeter GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_multimeter PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_multimeter PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_multimeter PUBLIC MikroSDK.Log)
add_subdirectory(lib_multimeter)
target_link_libraries(example_multimeter PUBLIC Click.Multimeter)
############################ example_multimeter GENERATED CODE END ###########################
