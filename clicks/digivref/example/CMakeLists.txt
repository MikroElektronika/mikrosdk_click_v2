cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_digivref LANGUAGES MikroC)
else()
    project(example_digivref LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_digivref
        main.c

)


############################ example_digivref GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_digivref PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_digivref PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_digivref PUBLIC MikroSDK.Log)
add_subdirectory(lib_digivref)
target_link_libraries(example_digivref PUBLIC Click.DigiVref)
############################ example_digivref GENERATED CODE END ###########################
