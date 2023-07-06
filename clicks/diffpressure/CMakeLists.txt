cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_diffpressure LANGUAGES MikroC)
else()
    project(example_diffpressure LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_diffpressure
        example/main.c

)


############################ example_diffpressure GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_diffpressure PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_diffpressure PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_diffpressure PUBLIC MikroSDK.Log)
add_subdirectory(lib_diffpressure)
target_link_libraries(example_diffpressure PUBLIC Click.Diffpressure)
############################ example_diffpressure GENERATED CODE END ###########################
