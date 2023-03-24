cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_dcmotor9 LANGUAGES MikroC)
else()
    project(example_dcmotor9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_dcmotor9
        main.c

)


############################ example_dcmotor9 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_dcmotor9 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_dcmotor9 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_dcmotor9 PUBLIC MikroSDK.Log)
add_subdirectory(lib_dcmotor9)
target_link_libraries(example_dcmotor9 PUBLIC Click.DcMotor9)
############################ example_dcmotor9 GENERATED CODE END ###########################
