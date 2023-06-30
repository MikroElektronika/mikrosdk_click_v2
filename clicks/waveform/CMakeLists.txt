cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_waveform LANGUAGES MikroC)
else()
    project(example_waveform LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_waveform
        example/main.c

)


############################ example_waveform GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_waveform PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_waveform PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_waveform PUBLIC MikroSDK.Log)
add_subdirectory(lib_waveform)
target_link_libraries(example_waveform PUBLIC Click.Waveform)
############################ example_waveform GENERATED CODE END ###########################
