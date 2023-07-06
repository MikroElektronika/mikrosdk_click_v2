cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hodcap LANGUAGES MikroC)
else()
    project(example_hodcap LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hodcap
        main.c
    
)


############################ example_hodcap GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hodcap PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hodcap PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hodcap PUBLIC MikroSDK.Log)
add_subdirectory(lib_hodcap)
target_link_libraries(example_hodcap PUBLIC Click.HODCAP)
############################ example_hodcap GENERATED CODE END ###########################

