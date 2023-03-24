cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_dcmotor17 LANGUAGES MikroC)
else()
    project(example_dcmotor17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_dcmotor17
        main.c

)


############################ example_dcmotor17 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_dcmotor17 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_dcmotor17 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_dcmotor17 PUBLIC MikroSDK.Log)
add_subdirectory(lib_dcmotor17)
target_link_libraries(example_dcmotor17 PUBLIC Click.DcMotor17)
############################ example_dcmotor17 GENERATED CODE END ###########################
