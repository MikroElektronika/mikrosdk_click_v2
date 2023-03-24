cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_adc16 LANGUAGES MikroC)
else()
    project(example_adc16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_adc16
        example/main.c

)


############################ example_adc16 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_adc16 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_adc16 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_adc16 PUBLIC MikroSDK.Log)
add_subdirectory(lib_adc16)
target_link_libraries(example_adc16 PUBLIC Click.ADC16)
############################ example_adc16 GENERATED CODE END ###########################
