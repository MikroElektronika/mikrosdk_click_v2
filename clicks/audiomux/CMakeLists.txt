cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_audiomux LANGUAGES MikroC)
else()
    project(example_audiomux LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_audiomux
        example/main.c

)


############################ example_audiomux GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_audiomux PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_audiomux PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_audiomux PUBLIC MikroSDK.Log)
add_subdirectory(lib_audiomux)
target_link_libraries(example_audiomux PUBLIC Click.AudioMUX)
############################ example_audiomux GENERATED CODE END ###########################
