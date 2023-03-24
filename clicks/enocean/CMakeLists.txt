cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_enocean LANGUAGES MikroC)
else()
    project(example_enocean LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_enocean
        example/main.c

)


############################ example_enocean GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_enocean PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_enocean PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_enocean PUBLIC MikroSDK.Log)
add_subdirectory(lib_enocean)
target_link_libraries(example_enocean PUBLIC Click.EnOcean)
############################ example_enocean GENERATED CODE END ###########################
