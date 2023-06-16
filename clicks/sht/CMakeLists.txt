cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_sht LANGUAGES MikroC)
else()
    project(example_sht LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_sht
        example/main.c

)


############################ example_sht GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_sht PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_sht PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_sht PUBLIC MikroSDK.Log)
add_subdirectory(lib_sht)
target_link_libraries(example_sht PUBLIC Click.Sht)
############################ example_sht GENERATED CODE END ###########################
