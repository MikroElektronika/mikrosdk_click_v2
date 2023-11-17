cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c2x2rgb LANGUAGES MikroC)
else()
    project(example_c2x2rgb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c2x2rgb
        example/main.c
    
)


############################ example_c2x2rgb GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c2x2rgb PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c2x2rgb PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c2x2rgb PUBLIC MikroSDK.Log)
add_subdirectory(lib_c2x2rgb)
target_link_libraries(example_c2x2rgb PUBLIC Click.2x2RGB)
############################ example_c2x2rgb GENERATED CODE END ###########################

