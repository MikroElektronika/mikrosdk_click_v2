cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_brushless25 LANGUAGES MikroC)
else()
    project(example_brushless25 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_brushless25
        example/main.c
    
)


############################ example_brushless25 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_brushless25 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_brushless25 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_brushless25 PUBLIC MikroSDK.Log)
add_subdirectory(lib_brushless25)
target_link_libraries(example_brushless25 PUBLIC Click.Brushless25)
############################ example_brushless25 GENERATED CODE END ###########################

