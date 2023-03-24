cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ble10 LANGUAGES MikroC)
else()
    project(example_ble10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ble10
        main.c

)


############################ example_ble10 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ble10 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ble10 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ble10 PUBLIC MikroSDK.Log)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_ble10 PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(example_ble10 PUBLIC MikroSDK.GenericPointer)
add_subdirectory(lib_ble10)
target_link_libraries(example_ble10 PUBLIC Click.BLE10)
############################ example_ble10 GENERATED CODE END ###########################
