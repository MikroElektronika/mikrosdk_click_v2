cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_brushless21 LANGUAGES MikroC)
else()
    project(example_brushless21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_brushless21
        main.c

)


############################ example_brushless21 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_brushless21 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_brushless21 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_brushless21 PUBLIC MikroSDK.Log)
add_subdirectory(lib_brushless21)
target_link_libraries(example_brushless21 PUBLIC Click.Brushless21)
############################ example_brushless21 GENERATED CODE END ###########################
