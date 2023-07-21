cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_oximeter LANGUAGES MikroC)
else()
    project(example_oximeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_oximeter
        example/main.c

)


############################ example_oximeter GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_oximeter PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_oximeter PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_oximeter PUBLIC MikroSDK.Log)
add_subdirectory(lib_oximeter)
target_link_libraries(example_oximeter PUBLIC Click.Oximeter)
############################ example_oximeter GENERATED CODE END ###########################
