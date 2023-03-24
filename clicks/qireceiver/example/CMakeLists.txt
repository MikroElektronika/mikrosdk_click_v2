cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_qireceiver LANGUAGES MikroC)
else()
    project(example_qireceiver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_qireceiver
        main.c

)


############################ example_qireceiver GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_qireceiver PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_qireceiver PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_qireceiver PUBLIC MikroSDK.Log)
add_subdirectory(lib_qireceiver)
target_link_libraries(example_qireceiver PUBLIC Click.QiReceiver)
############################ example_qireceiver GENERATED CODE END ###########################
