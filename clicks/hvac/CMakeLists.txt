cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hvac LANGUAGES MikroC)
else()
    project(example_hvac LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hvac
        example/main.c

)


############################ example_hvac GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hvac PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hvac PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hvac PUBLIC MikroSDK.Log)
add_subdirectory(lib_hvac)
target_link_libraries(example_hvac PUBLIC Click.Hvac)
############################ example_hvac GENERATED CODE END ###########################
