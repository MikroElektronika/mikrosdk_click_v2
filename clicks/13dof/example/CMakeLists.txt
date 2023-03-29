cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c13dof LANGUAGES MikroC)
else()
    project(example_c13dof LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c13dof
        main.c

)


############################ example_c13dof GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c13dof PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c13dof PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c13dof PUBLIC MikroSDK.Log)
add_subdirectory(lib_c13dof)
target_link_libraries(example_c13dof PUBLIC Click.13DOF)
############################ example_c13dof GENERATED CODE END ###########################
