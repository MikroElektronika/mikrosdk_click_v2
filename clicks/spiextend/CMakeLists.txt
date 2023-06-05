cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_spiextend LANGUAGES MikroC)
else()
    project(example_spiextend LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_spiextend
        example/main.c

)


############################ example_spiextend GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_spiextend PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_spiextend PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_spiextend PUBLIC MikroSDK.Log)
add_subdirectory(lib_spiextend)
target_link_libraries(example_spiextend PUBLIC Click.SPIExtend)
############################ example_spiextend GENERATED CODE END ###########################
