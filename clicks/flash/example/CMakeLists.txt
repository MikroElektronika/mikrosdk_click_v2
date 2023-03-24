cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_flash LANGUAGES MikroC)
else()
    project(example_flash LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_flash
        main.c

)


############################ example_flash GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_flash PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_flash PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_flash PUBLIC MikroSDK.Log)
add_subdirectory(lib_flash)
target_link_libraries(example_flash PUBLIC Click.Flash)
############################ example_flash GENERATED CODE END ###########################
