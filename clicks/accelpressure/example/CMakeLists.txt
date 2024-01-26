cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_accelpressure LANGUAGES MikroC)
else()
    project(example_accelpressure LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_accelpressure
        main.c
    
)


############################ example_accelpressure GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_accelpressure PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_accelpressure PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_accelpressure PUBLIC MikroSDK.Log)
add_subdirectory(lib_accelpressure)
target_link_libraries(example_accelpressure PUBLIC Click.AccelPressure)
############################ example_accelpressure GENERATED CODE END ###########################

