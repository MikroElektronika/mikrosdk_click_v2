cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_color15 LANGUAGES MikroC)
else()
    project(example_color15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_color15
        main.c

)


############################ example_color15 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_color15 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_color15 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_color15 PUBLIC MikroSDK.Log)
add_subdirectory(lib_color15)
target_link_libraries(example_color15 PUBLIC Click.Color15)
############################ example_color15 GENERATED CODE END ###########################
