cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_inclinometer4 LANGUAGES MikroC)
else()
    project(example_inclinometer4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_inclinometer4
        example/main.c
    
)


############################ example_inclinometer4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_inclinometer4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_inclinometer4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_inclinometer4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_inclinometer4)
target_link_libraries(example_inclinometer4 PUBLIC Click.Inclinometer4)
############################ example_inclinometer4 GENERATED CODE END ###########################

