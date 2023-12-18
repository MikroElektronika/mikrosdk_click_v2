cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_uwb3 LANGUAGES MikroC)
else()
    project(example_uwb3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_uwb3
        example/main.c
    
)


############################ example_uwb3 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_uwb3 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_uwb3 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_uwb3 PUBLIC MikroSDK.Log)
add_subdirectory(lib_uwb3)
target_link_libraries(example_uwb3 PUBLIC Click.UWB3)
############################ example_uwb3 GENERATED CODE END ###########################

