cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c8x8g LANGUAGES MikroC)
else()
    project(example_c8x8g LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c8x8g
        example/main.c

)


############################ example_c8x8g GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c8x8g PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c8x8g PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c8x8g PUBLIC MikroSDK.Log)
add_subdirectory(lib_c8x8g)
target_link_libraries(example_c8x8g PUBLIC Click.8x8G)
############################ example_c8x8g GENERATED CODE END ###########################
