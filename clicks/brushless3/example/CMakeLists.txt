cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_brushless3 LANGUAGES MikroC)
else()
    project(example_brushless3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_brushless3
        main.c

)


############################ example_brushless3 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_brushless3 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_brushless3 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_brushless3 PUBLIC MikroSDK.Log)
add_subdirectory(lib_brushless3)
target_link_libraries(example_brushless3 PUBLIC Click.Brushless3)
############################ example_brushless3 GENERATED CODE END ###########################
