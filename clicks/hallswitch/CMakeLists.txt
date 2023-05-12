cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hallswitch LANGUAGES MikroC)
else()
    project(example_hallswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hallswitch
        example/main.c

)


############################ example_hallswitch GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hallswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hallswitch PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hallswitch PUBLIC MikroSDK.Log)
add_subdirectory(lib_hallswitch)
target_link_libraries(example_hallswitch PUBLIC Click.HallSwitch)
############################ example_hallswitch GENERATED CODE END ###########################
