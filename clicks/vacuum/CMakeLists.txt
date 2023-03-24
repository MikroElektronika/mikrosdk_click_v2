cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_vacuum LANGUAGES MikroC)
else()
    project(example_vacuum LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_vacuum
        example/main.c

)


############################ example_vacuum GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_vacuum PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_vacuum PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_vacuum PUBLIC MikroSDK.Log)
add_subdirectory(lib_vacuum)
target_link_libraries(example_vacuum PUBLIC Click.Vacuum)
############################ example_vacuum GENERATED CODE END ###########################
