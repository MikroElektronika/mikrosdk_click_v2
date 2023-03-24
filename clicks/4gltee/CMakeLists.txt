cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c4gltee LANGUAGES MikroC)
else()
    project(example_c4gltee LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c4gltee
        example/main.c

)


############################ example_c4gltee GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c4gltee PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c4gltee PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c4gltee PUBLIC MikroSDK.Log)
add_subdirectory(lib_c4gltee)
target_link_libraries(example_c4gltee PUBLIC Click.4GLTEE)
############################ example_c4gltee GENERATED CODE END ###########################
