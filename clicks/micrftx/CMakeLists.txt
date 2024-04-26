cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_micrftx LANGUAGES MikroC)
else()
    project(example_micrftx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_micrftx
        example/main.c
    
)


############################ example_micrftx GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_micrftx PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_micrftx PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_micrftx PUBLIC MikroSDK.Log)
add_subdirectory(lib_micrftx)
target_link_libraries(example_micrftx PUBLIC Click.MICRFTX)
############################ example_micrftx GENERATED CODE END ###########################

