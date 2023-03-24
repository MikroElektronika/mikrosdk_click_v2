cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_smartdof LANGUAGES MikroC)
else()
    project(example_smartdof LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_smartdof
        example/main.c

)


############################ example_smartdof GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_smartdof PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_smartdof PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_smartdof PUBLIC MikroSDK.Log)
add_subdirectory(lib_smartdof)
target_link_libraries(example_smartdof PUBLIC Click.SmartDof)
############################ example_smartdof GENERATED CODE END ###########################
