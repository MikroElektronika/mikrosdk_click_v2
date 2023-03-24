cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_radar LANGUAGES MikroC)
else()
    project(example_radar LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_radar
        main.c

)


############################ example_radar GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_radar PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_radar PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_radar PUBLIC MikroSDK.Log)
add_subdirectory(lib_radar)
target_link_libraries(example_radar PUBLIC Click.Radar)
############################ example_radar GENERATED CODE END ###########################
