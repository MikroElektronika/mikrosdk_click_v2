cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hdc1000 LANGUAGES MikroC)
else()
    project(example_hdc1000 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hdc1000
        example/main.c

)


############################ example_hdc1000 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hdc1000 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hdc1000 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hdc1000 PUBLIC MikroSDK.Log)
add_subdirectory(lib_hdc1000)
target_link_libraries(example_hdc1000 PUBLIC Click.HDC1000)
############################ example_hdc1000 GENERATED CODE END ###########################
