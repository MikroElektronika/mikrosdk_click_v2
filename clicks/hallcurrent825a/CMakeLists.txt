cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hallcurrent825a LANGUAGES MikroC)
else()
    project(example_hallcurrent825a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hallcurrent825a
        example/main.c

)


############################ example_hallcurrent825a GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hallcurrent825a PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hallcurrent825a PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hallcurrent825a PUBLIC MikroSDK.Log)
add_subdirectory(lib_hallcurrent825a)
target_link_libraries(example_hallcurrent825a PUBLIC Click.HallCurrent825A)
############################ example_hallcurrent825a GENERATED CODE END ###########################
