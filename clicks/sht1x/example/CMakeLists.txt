cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_sht1x LANGUAGES MikroC)
else()
    project(example_sht1x LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_sht1x
        main.c

)


############################ example_sht1x GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_sht1x PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_sht1x PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_sht1x PUBLIC MikroSDK.Log)
add_subdirectory(lib_sht1x)
target_link_libraries(example_sht1x PUBLIC Click.Sht1x)
############################ example_sht1x GENERATED CODE END ###########################
