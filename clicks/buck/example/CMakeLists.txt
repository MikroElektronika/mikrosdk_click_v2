cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_buck LANGUAGES MikroC)
else()
    project(example_buck LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_buck
        main.c

)


############################ example_buck GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_buck PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_buck PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_buck PUBLIC MikroSDK.Log)
add_subdirectory(lib_buck)
target_link_libraries(example_buck PUBLIC Click.Buck)
############################ example_buck GENERATED CODE END ###########################
