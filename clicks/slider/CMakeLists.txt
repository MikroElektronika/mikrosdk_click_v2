cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_slider LANGUAGES MikroC)
else()
    project(example_slider LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_slider
        example/main.c

)


############################ example_slider GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_slider PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_slider PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_slider PUBLIC MikroSDK.Log)
add_subdirectory(lib_slider)
target_link_libraries(example_slider PUBLIC Click.Slider)
############################ example_slider GENERATED CODE END ###########################
