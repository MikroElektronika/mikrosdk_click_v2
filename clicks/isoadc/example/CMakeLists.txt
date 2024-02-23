cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_isoadc LANGUAGES MikroC)
else()
    project(example_isoadc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_isoadc
        main.c
    
)


############################ example_isoadc GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_isoadc PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_isoadc PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_isoadc PUBLIC MikroSDK.Log)
add_subdirectory(lib_isoadc)
target_link_libraries(example_isoadc PUBLIC Click.ISOADC)
############################ example_isoadc GENERATED CODE END ###########################

