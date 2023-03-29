cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rfmeter LANGUAGES MikroC)
else()
    project(example_rfmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rfmeter
        example/main.c

)


############################ example_rfmeter GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rfmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rfmeter PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rfmeter PUBLIC MikroSDK.Log)
add_subdirectory(lib_rfmeter)
target_link_libraries(example_rfmeter PUBLIC Click.RfMeter)
############################ example_rfmeter GENERATED CODE END ###########################
