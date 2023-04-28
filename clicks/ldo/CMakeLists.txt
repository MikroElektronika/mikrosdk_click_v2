cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ldo LANGUAGES MikroC)
else()
    project(example_ldo LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ldo
        example/main.c
    
)


############################ example_ldo GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ldo PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ldo PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ldo PUBLIC MikroSDK.Log)
add_subdirectory(lib_ldo)
target_link_libraries(example_ldo PUBLIC Click.LDO)
############################ example_ldo GENERATED CODE END ###########################

