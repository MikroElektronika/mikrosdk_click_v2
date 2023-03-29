cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_knob LANGUAGES MikroC)
else()
    project(example_knob LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_knob
        example/main.c

)


############################ example_knob GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_knob PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_knob PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_knob PUBLIC MikroSDK.Log)
add_subdirectory(lib_knob)
target_link_libraries(example_knob PUBLIC Click.Knob)
############################ example_knob GENERATED CODE END ###########################
