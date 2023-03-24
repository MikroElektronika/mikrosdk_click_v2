cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_grideye LANGUAGES MikroC)
else()
    project(example_grideye LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_grideye
        example/main.c

)


############################ example_grideye GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_grideye PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_grideye PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_grideye PUBLIC MikroSDK.Log)
add_subdirectory(lib_grideye)
target_link_libraries(example_grideye PUBLIC Click.Grideye)
############################ example_grideye GENERATED CODE END ###########################
