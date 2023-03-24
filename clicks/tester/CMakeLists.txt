cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_tester LANGUAGES MikroC)
else()
    project(example_tester LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_tester
        example/main.c

)


############################ example_tester GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_tester PUBLIC MikroC.Core)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_tester PUBLIC MikroSDK.Log)
add_subdirectory(lib_tester)
target_link_libraries(example_tester PUBLIC Click.Tester)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_tester PUBLIC MikroSDK.Board)
############################ example_tester GENERATED CODE END ###########################
