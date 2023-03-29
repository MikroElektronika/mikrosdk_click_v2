cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_vibromotor LANGUAGES MikroC)
else()
    project(example_vibromotor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_vibromotor
        main.c

)


############################ example_vibromotor GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_vibromotor PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_vibromotor PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_vibromotor PUBLIC MikroSDK.Log)
add_subdirectory(lib_vibromotor)
target_link_libraries(example_vibromotor PUBLIC Click.VibroMotor)
############################ example_vibromotor GENERATED CODE END ###########################
