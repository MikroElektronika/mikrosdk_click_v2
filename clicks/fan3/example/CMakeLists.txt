cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_fan3 LANGUAGES MikroC)
else()
    project(example_fan3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_fan3
        main.c

)


############################ example_fan3 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_fan3 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_fan3 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_fan3 PUBLIC MikroSDK.Log)
add_subdirectory(lib_fan3)
target_link_libraries(example_fan3 PUBLIC Click.Fan3)
############################ example_fan3 GENERATED CODE END ###########################
