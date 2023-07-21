cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_bletx LANGUAGES MikroC)
else()
    project(example_bletx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_bletx
        main.c

)


############################ example_bletx GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_bletx PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_bletx PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_bletx PUBLIC MikroSDK.Log)
add_subdirectory(lib_bletx)
target_link_libraries(example_bletx PUBLIC Click.BleTx)
############################ example_bletx GENERATED CODE END ###########################
