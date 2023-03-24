cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mbusrf4 LANGUAGES MikroC)
else()
    project(example_mbusrf4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mbusrf4
        main.c

)


############################ example_mbusrf4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mbusrf4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mbusrf4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mbusrf4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_mbusrf4)
target_link_libraries(example_mbusrf4 PUBLIC Click.MBusRf4)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(example_mbusrf4 PUBLIC MikroSDK.GenericPointer)
############################ example_mbusrf4 GENERATED CODE END ###########################
