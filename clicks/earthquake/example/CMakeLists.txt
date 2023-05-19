cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_earthquake LANGUAGES MikroC)
else()
    project(example_earthquake LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_earthquake
        main.c

)


############################ example_earthquake GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_earthquake PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_earthquake PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_earthquake PUBLIC MikroSDK.Log)
add_subdirectory(lib_earthquake)
target_link_libraries(example_earthquake PUBLIC Click.Earthquake)
############################ example_earthquake GENERATED CODE END ###########################
