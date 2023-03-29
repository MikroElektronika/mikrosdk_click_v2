cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_airflow LANGUAGES MikroC)
else()
    project(example_airflow LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_airflow
        example/main.c

)


############################ example_airflow GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_airflow PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_airflow PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_airflow PUBLIC MikroSDK.Log)
add_subdirectory(lib_airflow)
target_link_libraries(example_airflow PUBLIC Click.AirFlow)
############################ example_airflow GENERATED CODE END ###########################
