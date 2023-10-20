cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pressure23 LANGUAGES MikroC)
else()
    project(example_pressure23 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pressure23
        main.c
    
)


############################ example_pressure23 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pressure23 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pressure23 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pressure23 PUBLIC MikroSDK.Log)
add_subdirectory(lib_pressure23)
target_link_libraries(example_pressure23 PUBLIC Click.Pressure23)
############################ example_pressure23 GENERATED CODE END ###########################

