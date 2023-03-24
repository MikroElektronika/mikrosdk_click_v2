cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_thermok LANGUAGES MikroC)
else()
    project(example_thermok LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_thermok
        example/main.c

)


############################ example_thermok GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_thermok PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_thermok PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_thermok PUBLIC MikroSDK.Log)
add_subdirectory(lib_thermok)
target_link_libraries(example_thermok PUBLIC Click.ThermoK)
############################ example_thermok GENERATED CODE END ###########################
