cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_binhonova LANGUAGES MikroC)
else()
    project(example_binhonova LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_binhonova
        main.c
    
)


############################ example_binhonova GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_binhonova PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_binhonova PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_binhonova PUBLIC MikroSDK.Log)
add_subdirectory(lib_binhonova)
target_link_libraries(example_binhonova PUBLIC Click.BinhoNova)
############################ example_binhonova GENERATED CODE END ###########################

