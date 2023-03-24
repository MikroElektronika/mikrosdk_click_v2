cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_htu21d LANGUAGES MikroC)
else()
    project(example_htu21d LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_htu21d
        example/main.c

)


############################ example_htu21d GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_htu21d PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_htu21d PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_htu21d PUBLIC MikroSDK.Log)
add_subdirectory(lib_htu21d)
target_link_libraries(example_htu21d PUBLIC Click.Htu21d)
############################ example_htu21d GENERATED CODE END ###########################
