cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ft LANGUAGES MikroC)
else()
    project(example_ft LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ft
        main.c

)


############################ example_ft GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ft PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ft PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ft PUBLIC MikroSDK.Log)
add_subdirectory(lib_ft)
target_link_libraries(example_ft PUBLIC Click.Ft)
############################ example_ft GENERATED CODE END ###########################
