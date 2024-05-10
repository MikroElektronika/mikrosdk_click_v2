cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_cooler LANGUAGES MikroC)
else()
    project(example_cooler LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_cooler
        main.c
    
)


############################ example_cooler GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_cooler PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_cooler PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_cooler PUBLIC MikroSDK.Log)
add_subdirectory(lib_cooler)
target_link_libraries(example_cooler PUBLIC Click.Cooler)
############################ example_cooler GENERATED CODE END ###########################

