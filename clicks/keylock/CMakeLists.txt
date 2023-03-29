cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_keylock LANGUAGES MikroC)
else()
    project(example_keylock LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_keylock
        example/main.c

)


############################ example_keylock GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_keylock PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_keylock PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_keylock PUBLIC MikroSDK.Log)
add_subdirectory(lib_keylock)
target_link_libraries(example_keylock PUBLIC Click.Keylock)
############################ example_keylock GENERATED CODE END ###########################
