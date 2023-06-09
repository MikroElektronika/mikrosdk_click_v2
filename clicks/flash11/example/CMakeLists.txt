cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_flash11 LANGUAGES MikroC)
else()
    project(example_flash11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_flash11
        main.c
    
)


############################ example_flash11 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_flash11 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_flash11 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_flash11 PUBLIC MikroSDK.Log)
add_subdirectory(lib_flash11)
target_link_libraries(example_flash11 PUBLIC Click.Flash11)
############################ example_flash11 GENERATED CODE END ###########################

