cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_uv LANGUAGES MikroC)
else()
    project(example_uv LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_uv
        main.c

)


############################ example_uv GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_uv PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_uv PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_uv PUBLIC MikroSDK.Log)
add_subdirectory(lib_uv)
target_link_libraries(example_uv PUBLIC Click.Uv)
############################ example_uv GENERATED CODE END ###########################
