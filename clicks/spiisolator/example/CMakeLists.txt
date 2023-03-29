cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_spiisolator LANGUAGES MikroC)
else()
    project(example_spiisolator LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_spiisolator
        main.c

)


############################ example_spiisolator GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_spiisolator PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_spiisolator PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_spiisolator PUBLIC MikroSDK.Log)
add_subdirectory(lib_spiisolator)
target_link_libraries(example_spiisolator PUBLIC Click.Spiisolator)
############################ example_spiisolator GENERATED CODE END ###########################
