cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rs4855v LANGUAGES MikroC)
else()
    project(example_rs4855v LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rs4855v
        example/main.c

)


############################ example_rs4855v GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rs4855v PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rs4855v PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rs4855v PUBLIC MikroSDK.Log)
add_subdirectory(lib_rs4855v)
target_link_libraries(example_rs4855v PUBLIC Click.RS4855V)
############################ example_rs4855v GENERATED CODE END ###########################
