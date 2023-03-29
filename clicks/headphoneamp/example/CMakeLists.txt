cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_headphoneamp LANGUAGES MikroC)
else()
    project(example_headphoneamp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_headphoneamp
        main.c

)


############################ example_headphoneamp GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_headphoneamp PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_headphoneamp PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_headphoneamp PUBLIC MikroSDK.Log)
add_subdirectory(lib_headphoneamp)
target_link_libraries(example_headphoneamp PUBLIC Click.HeadphoneAMP)
############################ example_headphoneamp GENERATED CODE END ###########################
