cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_isoadc6 LANGUAGES MikroC)
else()
    project(example_isoadc6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_isoadc6
        main.c
    
)


############################ example_isoadc6 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_isoadc6 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_isoadc6 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_isoadc6 PUBLIC MikroSDK.Log)
add_subdirectory(lib_isoadc6)
target_link_libraries(example_isoadc6 PUBLIC Click.ISOADC6)
############################ example_isoadc6 GENERATED CODE END ###########################

