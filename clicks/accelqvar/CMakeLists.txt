cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_accelqvar LANGUAGES MikroC)
else()
    project(example_accelqvar LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_accelqvar
        example/main.c
    
)


############################ example_accelqvar GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_accelqvar PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_accelqvar PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_accelqvar PUBLIC MikroSDK.Log)
add_subdirectory(lib_accelqvar)
target_link_libraries(example_accelqvar PUBLIC Click.AccelQvar)
############################ example_accelqvar GENERATED CODE END ###########################

