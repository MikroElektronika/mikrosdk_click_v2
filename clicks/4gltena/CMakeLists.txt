cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c4gltena LANGUAGES MikroC)
else()
    project(example_c4gltena LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c4gltena
        example/main.c

)


############################ example_c4gltena GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c4gltena PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c4gltena PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c4gltena PUBLIC MikroSDK.Log)
add_subdirectory(lib_c4gltena)
target_link_libraries(example_c4gltena PUBLIC Click.4GLTENA)
############################ example_c4gltena GENERATED CODE END ###########################
