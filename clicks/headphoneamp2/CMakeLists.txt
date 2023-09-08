cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_headphoneamp2 LANGUAGES MikroC)
else()
    project(example_headphoneamp2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_headphoneamp2
        example/main.c
    
)


############################ example_headphoneamp2 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_headphoneamp2 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_headphoneamp2 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_headphoneamp2 PUBLIC MikroSDK.Log)
add_subdirectory(lib_headphoneamp2)
target_link_libraries(example_headphoneamp2 PUBLIC Click.HeadphoneAMP2)
############################ example_headphoneamp2 GENERATED CODE END ###########################

