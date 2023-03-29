cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_nanolr LANGUAGES MikroC)
else()
    project(example_nanolr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_nanolr
        main.c

)


############################ example_nanolr GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_nanolr PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_nanolr PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_nanolr PUBLIC MikroSDK.Log)
add_subdirectory(lib_nanolr)
target_link_libraries(example_nanolr PUBLIC Click.NanoLR)
############################ example_nanolr GENERATED CODE END ###########################
