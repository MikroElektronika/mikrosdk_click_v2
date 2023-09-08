cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_iotexpresslink LANGUAGES MikroC)
else()
    project(example_iotexpresslink LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_iotexpresslink
        example/main.c
    
)


############################ example_iotexpresslink GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_iotexpresslink PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_iotexpresslink PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_iotexpresslink PUBLIC MikroSDK.Log)
add_subdirectory(lib_iotexpresslink)
target_link_libraries(example_iotexpresslink PUBLIC Click.IoTExpressLink)
############################ example_iotexpresslink GENERATED CODE END ###########################

