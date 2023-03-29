cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_isoadc3 LANGUAGES MikroC)
else()
    project(example_isoadc3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_isoadc3
        example/main.c

)


############################ example_isoadc3 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_isoadc3 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_isoadc3 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_isoadc3 PUBLIC MikroSDK.Log)
add_subdirectory(lib_isoadc3)
target_link_libraries(example_isoadc3 PUBLIC Click.ISOADC3)
############################ example_isoadc3 GENERATED CODE END ###########################
