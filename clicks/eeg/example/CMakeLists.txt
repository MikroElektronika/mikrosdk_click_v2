cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_eeg LANGUAGES MikroC)
else()
    project(example_eeg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_eeg
        main.c

)


############################ example_eeg GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_eeg PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_eeg PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_eeg PUBLIC MikroSDK.Log)
add_subdirectory(lib_eeg)
target_link_libraries(example_eeg PUBLIC Click.EEG)
############################ example_eeg GENERATED CODE END ###########################
