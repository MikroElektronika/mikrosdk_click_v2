cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_wifible LANGUAGES MikroC)
else()
    project(example_wifible LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_wifible
        example/main.c

)


############################ example_wifible GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_wifible PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_wifible PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_wifible PUBLIC MikroSDK.Log)
add_subdirectory(lib_wifible)
target_link_libraries(example_wifible PUBLIC Click.WifiBle)
############################ example_wifible GENERATED CODE END ###########################
