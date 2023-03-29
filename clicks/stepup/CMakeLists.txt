cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_stepup LANGUAGES MikroC)
else()
    project(example_stepup LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_stepup
        example/main.c

)


############################ example_stepup GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_stepup PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_stepup PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_stepup PUBLIC MikroSDK.Log)
add_subdirectory(lib_stepup)
target_link_libraries(example_stepup PUBLIC Click.StepUp)
############################ example_stepup GENERATED CODE END ###########################
