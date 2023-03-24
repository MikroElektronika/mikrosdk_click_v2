cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_buttonr LANGUAGES MikroC)
else()
    project(example_buttonr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_buttonr
        example/main.c

)


############################ example_buttonr GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_buttonr PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_buttonr PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_buttonr PUBLIC MikroSDK.Log)
add_subdirectory(lib_buttonr)
target_link_libraries(example_buttonr PUBLIC Click.ButtonR)
############################ example_buttonr GENERATED CODE END ###########################
