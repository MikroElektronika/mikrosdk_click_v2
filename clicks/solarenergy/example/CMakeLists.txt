cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_solarenergy LANGUAGES MikroC)
else()
    project(example_solarenergy LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_solarenergy
        main.c

)


############################ example_solarenergy GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_solarenergy PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_solarenergy PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_solarenergy PUBLIC MikroSDK.Log)
add_subdirectory(lib_solarenergy)
target_link_libraries(example_solarenergy PUBLIC Click.SolarEnergy)
############################ example_solarenergy GENERATED CODE END ###########################
