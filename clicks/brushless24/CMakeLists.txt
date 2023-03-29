cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_brushless24 LANGUAGES MikroC)
else()
    project(example_brushless24 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_brushless24
        example/main.c

)


############################ example_brushless24 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_brushless24 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_brushless24 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_brushless24 PUBLIC MikroSDK.Log)
add_subdirectory(lib_brushless24)
target_link_libraries(example_brushless24 PUBLIC Click.Brushless24)
############################ example_brushless24 GENERATED CODE END ###########################
