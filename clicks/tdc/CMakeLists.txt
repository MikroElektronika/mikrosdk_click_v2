cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_tdc LANGUAGES MikroC)
else()
    project(example_tdc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_tdc
        example/main.c

)


############################ example_tdc GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_tdc PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_tdc PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_tdc PUBLIC MikroSDK.Log)
add_subdirectory(lib_tdc)
target_link_libraries(example_tdc PUBLIC Click.Tdc)
############################ example_tdc GENERATED CODE END ###########################
