cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_adc10 LANGUAGES MikroC)
else()
    project(example_adc10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_adc10
        example/main.c

)


############################ example_adc10 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_adc10 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_adc10 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_adc10 PUBLIC MikroSDK.Log)
add_subdirectory(lib_adc10)
target_link_libraries(example_adc10 PUBLIC Click.Adc10)
############################ example_adc10 GENERATED CODE END ###########################
