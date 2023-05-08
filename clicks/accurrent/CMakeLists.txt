cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_accurrent LANGUAGES MikroC)
else()
    project(example_accurrent LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_accurrent
        example/main.c

)


############################ example_accurrent GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_accurrent PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_accurrent PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_accurrent PUBLIC MikroSDK.Log)
add_subdirectory(lib_accurrent)
target_link_libraries(example_accurrent PUBLIC Click.AcCurrent)
############################ example_accurrent GENERATED CODE END ###########################
