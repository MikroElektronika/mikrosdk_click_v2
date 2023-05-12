cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_adswio LANGUAGES MikroC)
else()
    project(example_adswio LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_adswio
        example/main.c

)


############################ example_adswio GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_adswio PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_adswio PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_adswio PUBLIC MikroSDK.Log)
add_subdirectory(lib_adswio)
target_link_libraries(example_adswio PUBLIC Click.AdSwio)
############################ example_adswio GENERATED CODE END ###########################
