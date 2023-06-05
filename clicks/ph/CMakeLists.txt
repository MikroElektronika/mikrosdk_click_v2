cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ph LANGUAGES MikroC)
else()
    project(example_ph LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ph
        example/main.c

)


############################ example_ph GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ph PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ph PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ph PUBLIC MikroSDK.Log)
add_subdirectory(lib_ph)
target_link_libraries(example_ph PUBLIC Click.pH)
############################ example_ph GENERATED CODE END ###########################
