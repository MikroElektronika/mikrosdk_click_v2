cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_stretch LANGUAGES MikroC)
else()
    project(example_stretch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_stretch
        example/main.c

)


############################ example_stretch GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_stretch PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_stretch PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_stretch PUBLIC MikroSDK.Log)
add_subdirectory(lib_stretch)
target_link_libraries(example_stretch PUBLIC Click.Stretch)
############################ example_stretch GENERATED CODE END ###########################
