cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_radiostation LANGUAGES MikroC)
else()
    project(example_radiostation LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_radiostation
        example/main.c

)


############################ example_radiostation GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_radiostation PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_radiostation PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_radiostation PUBLIC MikroSDK.Log)
add_subdirectory(lib_radiostation)
target_link_libraries(example_radiostation PUBLIC Click.RadioStation)
############################ example_radiostation GENERATED CODE END ###########################
