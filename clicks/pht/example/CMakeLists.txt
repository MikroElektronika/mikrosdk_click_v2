cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pht LANGUAGES MikroC)
else()
    project(example_pht LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pht
        main.c

)


############################ example_pht GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pht PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pht PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pht PUBLIC MikroSDK.Log)
add_subdirectory(lib_pht)
target_link_libraries(example_pht PUBLIC Click.PHT)
############################ example_pht GENERATED CODE END ###########################
