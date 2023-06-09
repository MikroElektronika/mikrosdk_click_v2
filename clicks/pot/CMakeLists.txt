cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pot LANGUAGES MikroC)
else()
    project(example_pot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pot
        example/main.c

)


############################ example_pot GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pot PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pot PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pot PUBLIC MikroSDK.Log)
add_subdirectory(lib_pot)
target_link_libraries(example_pot PUBLIC Click.Pot)
############################ example_pot GENERATED CODE END ###########################
