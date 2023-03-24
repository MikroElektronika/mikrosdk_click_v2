cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mpu9dof LANGUAGES MikroC)
else()
    project(example_mpu9dof LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mpu9dof
        example/main.c

)


############################ example_mpu9dof GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mpu9dof PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mpu9dof PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mpu9dof PUBLIC MikroSDK.Log)
add_subdirectory(lib_mpu9dof)
target_link_libraries(example_mpu9dof PUBLIC Click.Mpu9Dof)
############################ example_mpu9dof GENERATED CODE END ###########################
