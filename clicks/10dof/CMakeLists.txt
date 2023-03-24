cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c10dof LANGUAGES MikroC)
else()
    project(example_c10dof LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c10dof
        example/main.c

)


############################ example_c10dof GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c10dof PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c10dof PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c10dof PUBLIC MikroSDK.Log)
add_subdirectory(lib_c10dof)
target_link_libraries(example_c10dof PUBLIC Click.10Dof)
############################ example_c10dof GENERATED CODE END ###########################
