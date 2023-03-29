cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mp32 LANGUAGES MikroC)
else()
    project(example_mp32 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mp32
        example/main.c

)


############################ example_mp32 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mp32 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mp32 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mp32 PUBLIC MikroSDK.Log)
add_subdirectory(lib_mp32)
target_link_libraries(example_mp32 PUBLIC Click.Mp32)
############################ example_mp32 GENERATED CODE END ###########################
