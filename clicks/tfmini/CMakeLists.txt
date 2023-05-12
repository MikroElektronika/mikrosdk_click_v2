cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_tfmini LANGUAGES MikroC)
else()
    project(example_tfmini LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_tfmini
        example/main.c

)


############################ example_tfmini GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_tfmini PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_tfmini PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_tfmini PUBLIC MikroSDK.Log)
add_subdirectory(lib_tfmini)
target_link_libraries(example_tfmini PUBLIC Click.TFmini)
############################ example_tfmini GENERATED CODE END ###########################
