cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_light LANGUAGES MikroC)
else()
    project(example_light LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_light
        example/main.c

)


############################ example_light GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_light PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_light PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_light PUBLIC MikroSDK.Log)
add_subdirectory(lib_light)
target_link_libraries(example_light PUBLIC Click.Light)
############################ example_light GENERATED CODE END ###########################
