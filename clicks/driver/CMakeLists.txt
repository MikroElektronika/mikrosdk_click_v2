cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_driver LANGUAGES MikroC)
else()
    project(example_driver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_driver
        example/main.c

)


############################ example_driver GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_driver PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_driver PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_driver PUBLIC MikroSDK.Log)
add_subdirectory(lib_driver)
target_link_libraries(example_driver PUBLIC Click.Driver)
############################ example_driver GENERATED CODE END ###########################
