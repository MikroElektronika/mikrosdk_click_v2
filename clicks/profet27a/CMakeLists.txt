cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_profet27a LANGUAGES MikroC)
else()
    project(example_profet27a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_profet27a
        example/main.c

)


############################ example_profet27a GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_profet27a PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_profet27a PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_profet27a PUBLIC MikroSDK.Log)
add_subdirectory(lib_profet27a)
target_link_libraries(example_profet27a PUBLIC Click.PROFET27A)
############################ example_profet27a GENERATED CODE END ###########################
