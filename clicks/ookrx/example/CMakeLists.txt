cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ookrx LANGUAGES MikroC)
else()
    project(example_ookrx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ookrx
        main.c
    
)


############################ example_ookrx GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ookrx PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ookrx PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ookrx PUBLIC MikroSDK.Log)
add_subdirectory(lib_ookrx)
target_link_libraries(example_ookrx PUBLIC Click.OOKRX)
############################ example_ookrx GENERATED CODE END ###########################

