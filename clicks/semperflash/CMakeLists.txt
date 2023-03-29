cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_semperflash LANGUAGES MikroC)
else()
    project(example_semperflash LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_semperflash
        example/main.c

)


############################ example_semperflash GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_semperflash PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_semperflash PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_semperflash PUBLIC MikroSDK.Log)
add_subdirectory(lib_semperflash)
target_link_libraries(example_semperflash PUBLIC Click.SemperFlash)
############################ example_semperflash GENERATED CODE END ###########################
