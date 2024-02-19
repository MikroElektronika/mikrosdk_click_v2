cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ledflash3 LANGUAGES MikroC)
else()
    project(example_ledflash3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ledflash3
        main.c
    
)


############################ example_ledflash3 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ledflash3 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ledflash3 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ledflash3 PUBLIC MikroSDK.Log)
add_subdirectory(lib_ledflash3)
target_link_libraries(example_ledflash3 PUBLIC Click.LEDFlash3)
############################ example_ledflash3 GENERATED CODE END ###########################

