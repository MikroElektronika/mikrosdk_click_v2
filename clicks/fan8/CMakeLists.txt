cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_fan8 LANGUAGES MikroC)
else()
    project(example_fan8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_fan8
        example/main.c

)


############################ example_fan8 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_fan8 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_fan8 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_fan8 PUBLIC MikroSDK.Log)
add_subdirectory(lib_fan8)
target_link_libraries(example_fan8 PUBLIC Click.FAN8)
############################ example_fan8 GENERATED CODE END ###########################
