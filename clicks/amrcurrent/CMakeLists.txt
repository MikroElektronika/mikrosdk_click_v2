cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_amrcurrent LANGUAGES MikroC)
else()
    project(example_amrcurrent LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_amrcurrent
        example/main.c

)


############################ example_amrcurrent GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_amrcurrent PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_amrcurrent PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_amrcurrent PUBLIC MikroSDK.Log)
add_subdirectory(lib_amrcurrent)
target_link_libraries(example_amrcurrent PUBLIC Click.AmrCurrent)
############################ example_amrcurrent GENERATED CODE END ###########################
