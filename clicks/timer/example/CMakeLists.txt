cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_timer LANGUAGES MikroC)
else()
    project(example_timer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_timer
        main.c

)


############################ example_timer GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_timer PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_timer PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_timer PUBLIC MikroSDK.Log)
add_subdirectory(lib_timer)
target_link_libraries(example_timer PUBLIC Click.Timer)
############################ example_timer GENERATED CODE END ###########################
