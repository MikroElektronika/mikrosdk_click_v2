cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_irbeacon LANGUAGES MikroC)
else()
    project(example_irbeacon LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_irbeacon
        main.c

)


############################ example_irbeacon GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_irbeacon PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_irbeacon PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_irbeacon PUBLIC MikroSDK.Log)
add_subdirectory(lib_irbeacon)
target_link_libraries(example_irbeacon PUBLIC Click.IrBeacon)
############################ example_irbeacon GENERATED CODE END ###########################
