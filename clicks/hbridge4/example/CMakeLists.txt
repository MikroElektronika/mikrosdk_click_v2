cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hbridge4 LANGUAGES MikroC)
else()
    project(example_hbridge4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hbridge4
        main.c

)


############################ example_hbridge4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hbridge4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hbridge4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hbridge4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_hbridge4)
target_link_libraries(example_hbridge4 PUBLIC Click.HBridge4)
############################ example_hbridge4 GENERATED CODE END ###########################
