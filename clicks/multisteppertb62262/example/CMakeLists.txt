cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_multisteppertb62262 LANGUAGES MikroC)
else()
    project(example_multisteppertb62262 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_multisteppertb62262
        main.c

)


############################ example_multisteppertb62262 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_multisteppertb62262 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_multisteppertb62262 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_multisteppertb62262 PUBLIC MikroSDK.Log)
add_subdirectory(lib_multisteppertb62262)
target_link_libraries(example_multisteppertb62262 PUBLIC Click.MultiStepperTB62262)
############################ example_multisteppertb62262 GENERATED CODE END ###########################
