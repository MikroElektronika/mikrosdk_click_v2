cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pir LANGUAGES MikroC)
else()
    project(example_pir LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pir
        example/main.c

)


############################ example_pir GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pir PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pir PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pir PUBLIC MikroSDK.Log)
add_subdirectory(lib_pir)
target_link_libraries(example_pir PUBLIC Click.Pir)
############################ example_pir GENERATED CODE END ###########################
