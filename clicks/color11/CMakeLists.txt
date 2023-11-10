cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_color11 LANGUAGES MikroC)
else()
    project(example_color11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_color11
        example/main.c
    
)


############################ example_color11 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_color11 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_color11 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_color11 PUBLIC MikroSDK.Log)
add_subdirectory(lib_color11)
target_link_libraries(example_color11 PUBLIC Click.Color11)
############################ example_color11 GENERATED CODE END ###########################

