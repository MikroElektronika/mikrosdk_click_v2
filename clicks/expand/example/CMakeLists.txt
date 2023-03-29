cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_expand LANGUAGES MikroC)
else()
    project(example_expand LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_expand
        main.c

)


############################ example_expand GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_expand PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_expand PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_expand PUBLIC MikroSDK.Log)
add_subdirectory(lib_expand)
target_link_libraries(example_expand PUBLIC Click.Expand)
############################ example_expand GENERATED CODE END ###########################
