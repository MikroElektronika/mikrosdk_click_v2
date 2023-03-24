cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_heartrate LANGUAGES MikroC)
else()
    project(example_heartrate LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_heartrate
        main.c

)


############################ example_heartrate GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_heartrate PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_heartrate PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_heartrate PUBLIC MikroSDK.Log)
add_subdirectory(lib_heartrate)
target_link_libraries(example_heartrate PUBLIC Click.HeartRate)
############################ example_heartrate GENERATED CODE END ###########################
