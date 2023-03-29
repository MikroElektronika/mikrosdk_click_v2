cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rs232spi LANGUAGES MikroC)
else()
    project(example_rs232spi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rs232spi
        main.c

)


############################ example_rs232spi GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rs232spi PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rs232spi PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rs232spi PUBLIC MikroSDK.Log)
add_subdirectory(lib_rs232spi)
target_link_libraries(example_rs232spi PUBLIC Click.Rs232Spi)
############################ example_rs232spi GENERATED CODE END ###########################
