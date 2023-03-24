cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rtkrover LANGUAGES MikroC)
else()
    project(example_rtkrover LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rtkrover
        main.c

)


############################ example_rtkrover GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rtkrover PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rtkrover PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rtkrover PUBLIC MikroSDK.Log)
add_subdirectory(lib_rtkrover)
target_link_libraries(example_rtkrover PUBLIC Click.RTKRover)
############################ example_rtkrover GENERATED CODE END ###########################
