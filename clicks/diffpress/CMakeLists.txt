cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_diffpress LANGUAGES MikroC)
else()
    project(example_diffpress LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_diffpress
        example/main.c

)


############################ example_diffpress GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_diffpress PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_diffpress PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_diffpress PUBLIC MikroSDK.Log)
add_subdirectory(lib_diffpress)
target_link_libraries(example_diffpress PUBLIC Click.DiffPress)
############################ example_diffpress GENERATED CODE END ###########################
