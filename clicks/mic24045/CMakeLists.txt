cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mic24045 LANGUAGES MikroC)
else()
    project(example_mic24045 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mic24045
        example/main.c

)


############################ example_mic24045 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mic24045 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mic24045 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mic24045 PUBLIC MikroSDK.Log)
add_subdirectory(lib_mic24045)
target_link_libraries(example_mic24045 PUBLIC Click.Mic24045)
############################ example_mic24045 GENERATED CODE END ###########################
