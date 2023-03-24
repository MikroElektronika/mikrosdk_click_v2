cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gsmgps LANGUAGES MikroC)
else()
    project(example_gsmgps LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gsmgps
        main.c

)


############################ example_gsmgps GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gsmgps PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gsmgps PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gsmgps PUBLIC MikroSDK.Log)
add_subdirectory(lib_gsmgps)
target_link_libraries(example_gsmgps PUBLIC Click.Gsmgps)
############################ example_gsmgps GENERATED CODE END ###########################
