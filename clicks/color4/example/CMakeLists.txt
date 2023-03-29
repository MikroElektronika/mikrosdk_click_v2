cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_color4 LANGUAGES MikroC)
else()
    project(example_color4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_color4
        main.c
    
)


############################ example_color4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_color4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_color4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_color4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_color4)
target_link_libraries(example_color4 PUBLIC Click.Color4)
############################ example_color4 GENERATED CODE END ###########################

