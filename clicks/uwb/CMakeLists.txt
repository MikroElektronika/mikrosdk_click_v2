cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_uwb LANGUAGES MikroC)
else()
    project(example_uwb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_uwb
        example/main.c

)


############################ example_uwb GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_uwb PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_uwb PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_uwb PUBLIC MikroSDK.Log)
add_subdirectory(lib_uwb)
target_link_libraries(example_uwb PUBLIC Click.Uwb)
############################ example_uwb GENERATED CODE END ###########################
