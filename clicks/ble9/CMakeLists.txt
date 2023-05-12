cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ble9 LANGUAGES MikroC)
else()
    project(example_ble9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ble9
        example/main.c

)


############################ example_ble9 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ble9 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ble9 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ble9 PUBLIC MikroSDK.Log)
add_subdirectory(lib_ble9)
target_link_libraries(example_ble9 PUBLIC Click.Ble9)
############################ example_ble9 GENERATED CODE END ###########################
