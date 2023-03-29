cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_zigbee LANGUAGES MikroC)
else()
    project(example_zigbee LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_zigbee
        main.c

)


############################ example_zigbee GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_zigbee PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_zigbee PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_zigbee PUBLIC MikroSDK.Log)
add_subdirectory(lib_zigbee)
target_link_libraries(example_zigbee PUBLIC Click.ZigBee)
############################ example_zigbee GENERATED CODE END ###########################
