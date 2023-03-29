cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_audiodac LANGUAGES MikroC)
else()
    project(example_audiodac LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_audiodac
        main.c
    
)


############################ example_audiodac GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_audiodac PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_audiodac PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_audiodac PUBLIC MikroSDK.Log)
add_subdirectory(lib_audiodac)
target_link_libraries(example_audiodac PUBLIC Click.AudioDAC)
############################ example_audiodac GENERATED CODE END ###########################

