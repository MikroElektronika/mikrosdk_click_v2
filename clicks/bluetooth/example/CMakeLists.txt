cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_bluetooth LANGUAGES MikroC)
else()
    project(example_bluetooth LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_bluetooth
        main.c

)


############################ example_bluetooth GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_bluetooth PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_bluetooth PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_bluetooth PUBLIC MikroSDK.Log)
add_subdirectory(lib_bluetooth)
target_link_libraries(example_bluetooth PUBLIC Click.Bluetooth)
############################ example_bluetooth GENERATED CODE END ###########################
