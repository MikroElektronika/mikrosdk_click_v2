cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_irsense LANGUAGES MikroC)
else()
    project(example_irsense LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_irsense
        main.c

)


############################ example_irsense GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_irsense PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_irsense PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_irsense PUBLIC MikroSDK.Log)
add_subdirectory(lib_irsense)
target_link_libraries(example_irsense PUBLIC Click.IrSense)
############################ example_irsense GENERATED CODE END ###########################
