cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mrangle LANGUAGES MikroC)
else()
    project(example_mrangle LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mrangle
        example/main.c

)


############################ example_mrangle GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mrangle PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mrangle PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mrangle PUBLIC MikroSDK.Log)
add_subdirectory(lib_mrangle)
target_link_libraries(example_mrangle PUBLIC Click.MrAngle)
############################ example_mrangle GENERATED CODE END ###########################
