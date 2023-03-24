cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_emg LANGUAGES MikroC)
else()
    project(example_emg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_emg
        main.c

)


############################ example_emg GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_emg PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_emg PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_emg PUBLIC MikroSDK.Log)
add_subdirectory(lib_emg)
target_link_libraries(example_emg PUBLIC Click.EMG)
############################ example_emg GENERATED CODE END ###########################
