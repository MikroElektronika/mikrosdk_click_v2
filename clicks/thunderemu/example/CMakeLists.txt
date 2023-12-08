cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_thunderemu LANGUAGES MikroC)
else()
    project(example_thunderemu LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_thunderemu
        main.c
    
)


############################ example_thunderemu GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_thunderemu PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_thunderemu PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_thunderemu PUBLIC MikroSDK.Log)
add_subdirectory(lib_thunderemu)
target_link_libraries(example_thunderemu PUBLIC Click.ThunderEMU)
############################ example_thunderemu GENERATED CODE END ###########################

