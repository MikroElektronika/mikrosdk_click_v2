cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_iqrf LANGUAGES MikroC)
else()
    project(example_iqrf LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_iqrf
        example/main.c

)


############################ example_iqrf GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_iqrf PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_iqrf PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_iqrf PUBLIC MikroSDK.Log)
add_subdirectory(lib_iqrf)
target_link_libraries(example_iqrf PUBLIC Click.iqRF)
############################ example_iqrf GENERATED CODE END ###########################
