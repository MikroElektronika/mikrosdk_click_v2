cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hallcurrent14 LANGUAGES MikroC)
else()
    project(example_hallcurrent14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hallcurrent14
        example/main.c

)


############################ example_hallcurrent14 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hallcurrent14 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hallcurrent14 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hallcurrent14 PUBLIC MikroSDK.Log)
add_subdirectory(lib_hallcurrent14)
target_link_libraries(example_hallcurrent14 PUBLIC Click.HallCurrent14)
############################ example_hallcurrent14 GENERATED CODE END ###########################
