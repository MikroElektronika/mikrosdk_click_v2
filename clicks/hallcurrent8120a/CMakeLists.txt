cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hallcurrent8120a LANGUAGES MikroC)
else()
    project(example_hallcurrent8120a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hallcurrent8120a
        example/main.c

)


############################ example_hallcurrent8120a GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hallcurrent8120a PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hallcurrent8120a PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hallcurrent8120a PUBLIC MikroSDK.Log)
add_subdirectory(lib_hallcurrent8120a)
target_link_libraries(example_hallcurrent8120a PUBLIC Click.HallCurrent8120A)
############################ example_hallcurrent8120a GENERATED CODE END ###########################
