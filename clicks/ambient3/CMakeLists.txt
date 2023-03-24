cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ambient3 LANGUAGES MikroC)
else()
    project(example_ambient3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ambient3
        example/main.c

)


############################ example_ambient3 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ambient3 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ambient3 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ambient3 PUBLIC MikroSDK.Log)
add_subdirectory(lib_ambient3)
target_link_libraries(example_ambient3 PUBLIC Click.Ambient3)
############################ example_ambient3 GENERATED CODE END ###########################
