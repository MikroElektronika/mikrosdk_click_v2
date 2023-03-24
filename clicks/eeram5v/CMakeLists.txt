cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_eeram5v LANGUAGES MikroC)
else()
    project(example_eeram5v LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_eeram5v
        example/main.c

)


############################ example_eeram5v GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_eeram5v PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_eeram5v PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_eeram5v PUBLIC MikroSDK.Log)
add_subdirectory(lib_eeram5v)
target_link_libraries(example_eeram5v PUBLIC Click.EERAM5V)
############################ example_eeram5v GENERATED CODE END ###########################
