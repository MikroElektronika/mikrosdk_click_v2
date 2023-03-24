cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_uvclight LANGUAGES MikroC)
else()
    project(example_uvclight LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_uvclight
        main.c

)


############################ example_uvclight GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_uvclight PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_uvclight PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_uvclight PUBLIC MikroSDK.Log)
add_subdirectory(lib_uvclight)
target_link_libraries(example_uvclight PUBLIC Click.UvcLight)
############################ example_uvclight GENERATED CODE END ###########################
