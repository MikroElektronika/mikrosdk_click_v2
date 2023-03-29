cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_current LANGUAGES MikroC)
else()
    project(example_current LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_current
        example/main.c

)


############################ example_current GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_current PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_current PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_current PUBLIC MikroSDK.Log)
add_subdirectory(lib_current)
target_link_libraries(example_current PUBLIC Click.Current)
############################ example_current GENERATED CODE END ###########################
