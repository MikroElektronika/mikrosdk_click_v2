cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rn4678 LANGUAGES MikroC)
else()
    project(example_rn4678 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rn4678
        main.c

)


############################ example_rn4678 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rn4678 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rn4678 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rn4678 PUBLIC MikroSDK.Log)
add_subdirectory(lib_rn4678)
target_link_libraries(example_rn4678 PUBLIC Click.Rn4678)
############################ example_rn4678 GENERATED CODE END ###########################
