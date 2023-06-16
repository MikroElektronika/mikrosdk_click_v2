cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_shake2wake LANGUAGES MikroC)
else()
    project(example_shake2wake LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_shake2wake
        example/main.c

)


############################ example_shake2wake GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_shake2wake PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_shake2wake PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_shake2wake PUBLIC MikroSDK.Log)
add_subdirectory(lib_shake2wake)
target_link_libraries(example_shake2wake PUBLIC Click.Shake2Wake)
############################ example_shake2wake GENERATED CODE END ###########################
