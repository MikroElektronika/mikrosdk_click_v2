cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_dotmatrixr LANGUAGES MikroC)
else()
    project(example_dotmatrixr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_dotmatrixr
        main.c

)


############################ example_dotmatrixr GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_dotmatrixr PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_dotmatrixr PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_dotmatrixr PUBLIC MikroSDK.Log)
add_subdirectory(lib_dotmatrixr)
target_link_libraries(example_dotmatrixr PUBLIC Click.DotMatrixR)
############################ example_dotmatrixr GENERATED CODE END ###########################
