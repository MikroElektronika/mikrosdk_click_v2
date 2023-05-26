cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_g2c3g LANGUAGES MikroC)
else()
    project(example_g2c3g LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_g2c3g
        example/main.c
    
)


############################ example_g2c3g GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_g2c3g PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_g2c3g PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_g2c3g PUBLIC MikroSDK.Log)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_g2c3g PUBLIC MikroSDK.Conversions)
add_subdirectory(lib_g2c3g)
target_link_libraries(example_g2c3g PUBLIC Click.G2C3G)
############################ example_g2c3g GENERATED CODE END ###########################

