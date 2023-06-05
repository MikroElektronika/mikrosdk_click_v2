cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_illuminance LANGUAGES MikroC)
else()
    project(example_illuminance LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_illuminance
        example/main.c

)


############################ example_illuminance GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_illuminance PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_illuminance PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_illuminance PUBLIC MikroSDK.Log)
add_subdirectory(lib_illuminance)
target_link_libraries(example_illuminance PUBLIC Click.Illuminance)
############################ example_illuminance GENERATED CODE END ###########################
