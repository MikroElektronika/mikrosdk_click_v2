cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c4x4key LANGUAGES MikroC)
else()
    project(example_c4x4key LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c4x4key
        main.c

)


############################ example_c4x4key GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c4x4key PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c4x4key PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c4x4key PUBLIC MikroSDK.Log)
add_subdirectory(lib_c4x4key)
target_link_libraries(example_c4x4key PUBLIC Click.4x4Key)
############################ example_c4x4key GENERATED CODE END ###########################
