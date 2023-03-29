cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_force LANGUAGES MikroC)
else()
    project(example_force LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_force
        example/main.c

)


############################ example_force GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_force PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_force PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_force PUBLIC MikroSDK.Log)
add_subdirectory(lib_force)
target_link_libraries(example_force PUBLIC Click.Force)
############################ example_force GENERATED CODE END ###########################
