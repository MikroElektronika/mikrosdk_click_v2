cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_dcmotor5 LANGUAGES MikroC)
else()
    project(example_dcmotor5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_dcmotor5
        main.c

)


############################ example_dcmotor5 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_dcmotor5 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_dcmotor5 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_dcmotor5 PUBLIC MikroSDK.Log)
add_subdirectory(lib_dcmotor5)
target_link_libraries(example_dcmotor5 PUBLIC Click.DcMotor5)
############################ example_dcmotor5 GENERATED CODE END ###########################
