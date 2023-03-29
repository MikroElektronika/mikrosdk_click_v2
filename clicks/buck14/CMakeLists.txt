cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_buck14 LANGUAGES MikroC)
else()
    project(example_buck14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_buck14
        example/main.c

)


############################ example_buck14 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_buck14 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_buck14 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_buck14 PUBLIC MikroSDK.Log)
add_subdirectory(lib_buck14)
target_link_libraries(example_buck14 PUBLIC Click.Buck14)
############################ example_buck14 GENERATED CODE END ###########################
