cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_shtan LANGUAGES MikroC)
else()
    project(example_shtan LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_shtan
        example/main.c

)


############################ example_shtan GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_shtan PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_shtan PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_shtan PUBLIC MikroSDK.Log)
add_subdirectory(lib_shtan)
target_link_libraries(example_shtan PUBLIC Click.ShtAn)
############################ example_shtan GENERATED CODE END ###########################
