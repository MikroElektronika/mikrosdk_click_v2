cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_fever LANGUAGES MikroC)
else()
    project(example_fever LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_fever
        main.c

)


############################ example_fever GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_fever PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_fever PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_fever PUBLIC MikroSDK.Log)
add_subdirectory(lib_fever)
target_link_libraries(example_fever PUBLIC Click.Fever)
############################ example_fever GENERATED CODE END ###########################
