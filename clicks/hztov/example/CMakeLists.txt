cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hztov LANGUAGES MikroC)
else()
    project(example_hztov LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hztov
        main.c

)


############################ example_hztov GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hztov PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hztov PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hztov PUBLIC MikroSDK.Log)
add_subdirectory(lib_hztov)
target_link_libraries(example_hztov PUBLIC Click.HzToV)
############################ example_hztov GENERATED CODE END ###########################
