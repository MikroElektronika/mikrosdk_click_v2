cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_multisteppertb62261 LANGUAGES MikroC)
else()
    project(example_multisteppertb62261 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_multisteppertb62261
        main.c

)


############################ example_multisteppertb62261 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_multisteppertb62261 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_multisteppertb62261 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_multisteppertb62261 PUBLIC MikroSDK.Log)
add_subdirectory(lib_multisteppertb62261)
target_link_libraries(example_multisteppertb62261 PUBLIC Click.MultiStepperTB62261)
############################ example_multisteppertb62261 GENERATED CODE END ###########################
