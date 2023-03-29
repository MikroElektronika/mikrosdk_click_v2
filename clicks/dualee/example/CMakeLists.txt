cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_dualee LANGUAGES MikroC)
else()
    project(example_dualee LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_dualee
        main.c

)


############################ example_dualee GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_dualee PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_dualee PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_dualee PUBLIC MikroSDK.Log)
add_subdirectory(lib_dualee)
target_link_libraries(example_dualee PUBLIC Click.DualEE)
############################ example_dualee GENERATED CODE END ###########################
