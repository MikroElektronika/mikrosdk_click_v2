cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_canbus LANGUAGES MikroC)
else()
    project(example_canbus LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_canbus
        main.c

)


############################ example_canbus GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_canbus PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_canbus PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_canbus PUBLIC MikroSDK.Log)
add_subdirectory(lib_canbus)
target_link_libraries(example_canbus PUBLIC Click.CanBus)
############################ example_canbus GENERATED CODE END ###########################
