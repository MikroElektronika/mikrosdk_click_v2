cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_timerrelay LANGUAGES MikroC)
else()
    project(example_timerrelay LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_timerrelay
        main.c
    
)


############################ example_timerrelay GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_timerrelay PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_timerrelay PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_timerrelay PUBLIC MikroSDK.Log)
add_subdirectory(lib_timerrelay)
target_link_libraries(example_timerrelay PUBLIC Click.TimerRelay)
############################ example_timerrelay GENERATED CODE END ###########################

