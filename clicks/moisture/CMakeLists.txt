cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_moisture LANGUAGES MikroC)
else()
    project(example_moisture LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_moisture
        example/main.c

)


############################ example_moisture GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_moisture PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_moisture PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_moisture PUBLIC MikroSDK.Log)
add_subdirectory(lib_moisture)
target_link_libraries(example_moisture PUBLIC Click.Moisture)
############################ example_moisture GENERATED CODE END ###########################
