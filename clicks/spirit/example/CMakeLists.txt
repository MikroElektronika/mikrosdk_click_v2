cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_spirit LANGUAGES MikroC)
else()
    project(example_spirit LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_spirit
        main.c

)


############################ example_spirit GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_spirit PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_spirit PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_spirit PUBLIC MikroSDK.Log)
add_subdirectory(lib_spirit)
target_link_libraries(example_spirit PUBLIC Click.SPIRIT)
############################ example_spirit GENERATED CODE END ###########################
