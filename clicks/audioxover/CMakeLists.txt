cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_audioxover LANGUAGES MikroC)
else()
    project(example_audioxover LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_audioxover
        example/main.c

)


############################ example_audioxover GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_audioxover PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_audioxover PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_audioxover PUBLIC MikroSDK.Log)
add_subdirectory(lib_audioxover)
target_link_libraries(example_audioxover PUBLIC Click.AudioXover)
############################ example_audioxover GENERATED CODE END ###########################
