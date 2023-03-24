cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_irgesture LANGUAGES MikroC)
else()
    project(example_irgesture LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_irgesture
        example/main.c

)


############################ example_irgesture GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_irgesture PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_irgesture PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_irgesture PUBLIC MikroSDK.Log)
add_subdirectory(lib_irgesture)
target_link_libraries(example_irgesture PUBLIC Click.IrGesture)
############################ example_irgesture GENERATED CODE END ###########################
