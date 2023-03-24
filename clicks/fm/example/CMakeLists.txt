cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_fm LANGUAGES MikroC)
else()
    project(example_fm LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_fm
        main.c

)


############################ example_fm GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_fm PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_fm PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_fm PUBLIC MikroSDK.Log)
add_subdirectory(lib_fm)
target_link_libraries(example_fm PUBLIC Click.Fm)
############################ example_fm GENERATED CODE END ###########################
