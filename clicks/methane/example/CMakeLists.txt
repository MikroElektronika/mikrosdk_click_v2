cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_methane LANGUAGES MikroC)
else()
    project(example_methane LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_methane
        main.c

)


############################ example_methane GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_methane PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_methane PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_methane PUBLIC MikroSDK.Log)
add_subdirectory(lib_methane)
target_link_libraries(example_methane PUBLIC Click.Methane)
############################ example_methane GENERATED CODE END ###########################
