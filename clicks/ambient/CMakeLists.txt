cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ambient LANGUAGES MikroC)
else()
    project(example_ambient LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ambient
        example/main.c

)


############################ example_ambient GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ambient PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ambient PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ambient PUBLIC MikroSDK.Log)
add_subdirectory(lib_ambient)
target_link_libraries(example_ambient PUBLIC Click.Ambient)
############################ example_ambient GENERATED CODE END ###########################
